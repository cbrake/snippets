package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"math"
	"os"
)

// golang types
// uint8       the set of all unsigned  8-bit (1 byte) integers (0 to 255)
// uint16      the set of all unsigned 16-bit (2 byte) integers (0 to 65535)
// uint32      the set of all unsigned 32-bit (4 byte) integers (0 to 4294967295)
// uint64      the set of all unsigned 64-bit (8 byte) integers (0 to 18446744073709551615)

// http://soundfile.sapp.org/doc/WaveFormat/
// The default byte ordering assumed for WAVE data files is little-endian.
// Files written using the big-endian byte ordering scheme have the identifier RIFX instead of RIFF.
type wavfileHeader struct {

	// Offset 0
	// Contains the letters "RIFF" in ASCII form
	riffTag [4]uint8 // ChunkID 4 bytes

	// Offset 4
	// This is the size of the entire file in bytes minus 8 bytes for the two fields not included in this count: ChunkID and ChunkSize.
	// Also = 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
	riffLength uint32 // ChunkSize 4 bytes

	// Offset 8
	// Contains the letters "WAVE"
	waveTag [4]uint8 // Format 4 bytes

	// Offset 12
	// Contains the letters "fmt "
	fmtTag [4]uint8 // Subchunk1ID 4 bytes

	// Offset 16
	// 16 for PCM
	fmtLength uint32 // Subchunk1Size 4 bytes

	// Offset 20
	// PCM = 1 (i.e. Linear quantization)
	// Values other than 1 indicate some form of compression.
	audioFormat uint16 // AudioFormat 2 bytes

	// Offset 22
	// Mono = 1, Stereo = 2
	numChannels uint16 // NumChannels 2 bytes

	// Offset 24
	// 44100, 96000 etc
	sampleRate uint32 // SampleRate 4 bytes

	// Offset 28
	// = SampleRate * NumChannels * BitsPerSample/8
	byteRate uint32 // ByteRate 4 bytes

	// Offset 32
	// The number of bytes for one sample including all channels.
	// = NumChannels * BitsPerSample/8
	blockAlign uint16 // BlockAlign 2 bytes

	// Offset 34
	// 8 bits = 8, 16 bits = 16
	bitsPerSample uint16 // BitsPerSample 2 bytes

	// Offset 36
	// Contains the letters "data"
	dataTag [4]uint8 // Subchunk2ID 4 bytes

	// Offset 40
	// This is the number of bytes in the data.
	// = NumSamples * NumChannels * BitsPerSample/8
	dataLength uint32 // Subchunk2Size 4 bytes
}

// Convert the wavfileHeader struct to a byte slice
func (h *wavfileHeader) ToBytes() []byte {
	buffer := new(bytes.Buffer)
	binary.Write(buffer, binary.LittleEndian, h)
	return buffer.Bytes()
}

// Create a file and return it for further writing of audio data.
func open(filename string, samplesPerSecond uint32, bitsPerSample uint8, channels uint16) *os.File {

	fmt.Printf("Creating file %v\n", filename)
	file, err := os.Create("./" + filename)
	failOnError(err)

	header := &wavfileHeader{}

	copy(header.riffTag[:], "RIFF")
	copy(header.waveTag[:], "WAVE")
	copy(header.fmtTag[:], "fmt ")
	copy(header.dataTag[:], "data")

	header.riffLength = 0
	header.fmtLength = 16
	header.audioFormat = 1
	header.numChannels = channels
	header.sampleRate = samplesPerSecond
	header.byteRate = samplesPerSecond * uint32(header.numChannels) * uint32(bitsPerSample/8)
	header.blockAlign = header.numChannels * uint16(bitsPerSample/8)
	header.bitsPerSample = uint16(bitsPerSample)
	header.dataLength = 0

	fmt.Println("Writing header")
	file.Write(header.ToBytes())

	return file
}

func write(file *os.File, waveform []uint16) {

	// We need to write to the file as a []uint8 slice.
	// Convert our []uint16 waveform slice into []uint8.
	data := make([]uint8, len(waveform)*2)
	j := 0
	for _, val := range waveform {
		var h, l uint8 = uint8(val >> 8), uint8(val & 0xff)
		data[j] = l
		j++
		data[j] = h
		j++
	}

	// Write the data starting at offset 44, which is the first offset after the header.
	fmt.Println("Writing data")
	file.WriteAt(data, 44)

}

func close(file *os.File) {

	// Ensure that the file is closed, no matter what
	defer file.Close()

	// file.Stat() allows us to get access to the size of the file (among other things)
	fileInfo, err := file.Stat()
	failOnError(err)

	var (
		fileLength        uint32 = uint32(fileInfo.Size())
		wavfileHeaderSize uint32 = 44 // bytes
		riffLength        uint32 = fileLength - 8
		dataLength        uint32 = fileLength - wavfileHeaderSize
	)

	fmt.Println("Updating header")

	// Write the riffLength into the header
	rl := make([]byte, 4)
	binary.LittleEndian.PutUint32(rl, riffLength)
	file.WriteAt(rl, 4)

	// Write the length of the file into the header
	// The dataLength header starts at offset 40
	dl := make([]byte, 4)
	binary.LittleEndian.PutUint32(dl, dataLength)
	file.WriteAt(dl, 40)

}

func failOnError(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {

	var (
		argFileName   string
		argSampleRate uint
		argDuration   uint
		argVolume     uint
		argFrequency  float64
	)

	flag.StringVar(&argFileName, "filename", "sin.wav", "The name of the file to write to.")
	flag.UintVar(&argSampleRate, "samplerate", 44100, "The sample rate. E.g. 44100, 96000, 192000")
	flag.UintVar(&argDuration, "duration", 5, "The duration in seconds.")
	flag.UintVar(&argVolume, "volume", 28000, "The volume (range between 0 and 32767).")
	flag.Float64Var(&argFrequency, "frequency", 440.0, "The frequency of the sine wave (e.g. 440Hz)")

	flag.Parse()

	var (
		bitsPerSample    uint8   = 16
		samplesPerSecond uint32  = uint32(argSampleRate)                  // The number of samples per second
		numberOfSamples  uint32  = samplesPerSecond * uint32(argDuration) // This is the length of the sound file in seconds
		frequency                = argFrequency
		volume           uint32  = uint32(argVolume)
		volumedB         float64 = 20 * math.Log10(float64(volume)/32767)
		phase            float64
		waveform         []uint16 = make([]uint16, numberOfSamples)
	)

	fmt.Printf("Generating sine wave at %v Hz, %v dB (%v), using %v samples per second, for %v seconds\n", argFrequency, volumedB, argVolume, argSampleRate, argDuration)
	var frequencyRadiansPerSample = frequency * 2 * math.Pi / float64(samplesPerSecond)
	for sample := uint32(0); sample < numberOfSamples; sample++ {
		phase += frequencyRadiansPerSample
		sampleValue := float64(volume) * math.Sin(phase)
		waveform[sample] = uint16(sampleValue)
	}

	file := open(argFileName, samplesPerSecond, bitsPerSample, 2)
	write(file, waveform)
	close(file)

	fmt.Println("Done")
}
