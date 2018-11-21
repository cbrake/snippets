package packet

import (
	"bytes"
	"compress/gzip"
	"compress/zlib"
	"encoding/gob"
	"encoding/json"

	"github.com/gogo/protobuf/proto"
)

// EncodeJSONGzip takes a packet(s) and encodes using JSON and then Gzip
func EncodeJSONGzip(p interface{}) (data []byte, err error) {
	b := bytes.Buffer{}
	compressor, err := gzip.NewWriterLevel(&b, gzip.BestCompression)
	if err != nil {
		return
	}
	encoder := json.NewEncoder(compressor)
	err = encoder.Encode(p)
	if err != nil {
		return
	}
	err = compressor.Close()
	if err != nil {
		return
	}

	data = b.Bytes()
	return
}

// EncodeJSONZlib takes a packet(s) and encodes using JSON and then zlib
func EncodeJSONZlib(p interface{}) (data []byte, err error) {
	b := bytes.Buffer{}
	compressor, err := zlib.NewWriterLevel(&b, zlib.BestCompression)
	if err != nil {
		return
	}
	encoder := json.NewEncoder(compressor)
	err = encoder.Encode(p)
	if err != nil {
		return
	}
	err = compressor.Close()
	if err != nil {
		return
	}

	data = b.Bytes()
	return
}

// EncodeGob takes a packet(s) and encodes using Gob
func EncodeGob(p interface{}) (data []byte, err error) {
	b := bytes.Buffer{}
	encoder := gob.NewEncoder(&b)
	err = encoder.Encode(p)
	if err != nil {
		return
	}
	data = b.Bytes()
	return
}

// EncodeGobGzip takes a packet(s) and encodes using Gob and then Gzip
func EncodeGobGzip(p interface{}) (data []byte, err error) {
	b := bytes.Buffer{}
	compressor, err := gzip.NewWriterLevel(&b, gzip.BestCompression)
	if err != nil {
		return
	}
	encoder := gob.NewEncoder(compressor)
	err = encoder.Encode(p)
	if err != nil {
		return
	}
	err = compressor.Close()
	if err != nil {
		return
	}

	data = b.Bytes()
	return
}

// EncodeGobZlib takes a packet(s) and encodes using Gob and then Zlib
func EncodeGobZlib(p interface{}) (data []byte, err error) {
	b := bytes.Buffer{}
	compressor, err := zlib.NewWriterLevel(&b, zlib.BestCompression)
	if err != nil {
		return
	}
	encoder := gob.NewEncoder(compressor)
	err = encoder.Encode(p)
	if err != nil {
		return
	}
	err = compressor.Close()
	if err != nil {
		return
	}

	data = b.Bytes()
	return
}

// EncodePb returns a raw protobuf
func EncodePb(p proto.Message) (data []byte, err error) {
	data, err = proto.Marshal(p)
	return
}

// EncodePbZlib returns a protobuf and then zlib compress
func EncodePbZlib(p proto.Message) (data []byte, err error) {

	b := bytes.Buffer{}
	compressor, err := zlib.NewWriterLevel(&b, zlib.BestCompression)
	if err != nil {
		return
	}

	dPb, err := proto.Marshal(p)
	dataB := bytes.NewBuffer(dPb)

	_, err = dataB.WriteTo(compressor)

	if err != nil {
		return
	}

	err = compressor.Close()
	if err != nil {
		return
	}

	data = b.Bytes()

	return
}
