#!/usr/bin/python
####################################################
from Numeric import floor, arange, sin, pi
import wave

#init output and related vars
samplesPerSecond = [8000, 16000, 44100]
freq = [50, 1000, 2000, 5000, 10000, 19000]
time_len = 5

#samplesPerSecond = [8000]
#freq = [1000]
#time_len = 300

def gen_wav(seconds, frequency, amplitudePercentOfMax, samplesPerSecond):
	# calculate frequency as radians/sample
	radiansPerSample = (2.0 * pi * frequency) / samplesPerSecond
	numberOfSamples = int(seconds*samplesPerSecond)
	maxAmplitude = (amplitudePercentOfMax / 100.0) * 32767
	samples = sin(arange(numberOfSamples) * radiansPerSample) * maxAmplitude
	# round and convert to array of 16-bit shorts
	return floor(samples + 0.5).astype('s')

if __name__ == '__main__':
	# generate test sample wave files
	for sps in samplesPerSecond:
		for f in freq:
			filename = '%iHz_%iSR_%is.wav' % (f,sps,time_len)
			Outfile = wave.open(filename, "w")
			Outfile.setnchannels(1)
			Outfile.setsampwidth(2) # 2 bytes for 32767 amplitude
			Outfile.setframerate(sps)
			Outfile.setcomptype("NONE", "Uncompressed")

			sampleArray = gen_wav(time_len, f, 100, sps)
			Outfile.writeframes(sampleArray.tostring()) # little-endian cpu only
			Outfile.close()


