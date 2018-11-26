// This program tests if an unused field takes up any space in a protobuf packet
package main

import (
	"fmt"
	"time"

	"github.com/cbrake/snippets/go/packet"
	"github.com/gogo/protobuf/proto"
	"github.com/golang/protobuf/ptypes"
	log "github.com/mgutz/logxi/v1"
)

func main() {
	ts, _ := ptypes.TimestampProto(time.Now())
	s := &packet.Sample{
		Id:    "ET23B",
		Type:  packet.Sample_ANALOG,
		Index: int32(2),
		Value: 2.1232,
		Time:  ts,
	}

	sDurationZero := &packet.SampleDuration{
		Id:    "ET23B",
		Type:  packet.SampleDuration_ANALOG,
		Index: int32(2),
		Value: 2.1232,
		Time:  ts,
	}

	sDuration := &packet.SampleDuration{
		Id:       "ET23B",
		Type:     packet.SampleDuration_ANALOG,
		Index:    int32(2),
		Value:    2.1232,
		Time:     ts,
		Duration: 2342.23,
	}

	sPb, err := proto.Marshal(s)
	if err != nil {
		log.Error("can't encode s: ", err)
	}

	sDurationZeroPb, err := proto.Marshal(sDurationZero)
	if err != nil {
		log.Error("can't encode sDurationZero: ", err)
	}

	sDurationPb, err := proto.Marshal(sDuration)
	if err != nil {
		log.Error("can't encode sDuration: ", err)
	}

	fmt.Printf("Sample len: %v, SampleDuration with zero dur: %v, SampleDuration: %v\n",
		len(sPb), len(sDurationZeroPb), len(sDurationPb))
}

// program results
// Sample len: 28, SampleDuration with zero dur: 28, SampleDuration: 33
