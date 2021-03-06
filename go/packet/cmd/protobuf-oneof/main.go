package main

import (
	"fmt"
	"time"

	"github.com/cbrake/snippets/go/packet"
	"github.com/gogo/protobuf/proto"
	"github.com/golang/protobuf/ptypes"
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

	bS, err := packet.EncodePb(s)
	if err != nil {
		fmt.Println("Error encoding packet: ", err)
	}

	p := &packet.Packet{
		Contents: &packet.Packet_Sample{Sample: s},
	}

	bP, err := packet.EncodePb(p)
	if err != nil {
		fmt.Println("Error encoding packet: ", err)
	}

	fmt.Printf("sample: %v bytes, packet: %v bytes\n",
		len(bS), len(bP))

	fmt.Printf("protobuf oneof overhead is %v bytes per packet\n",
		len(bP)-len(bS))

	// test decoding the packet
	pDecode := &packet.Packet{}

	err = proto.Unmarshal(bP, pDecode)
	if err != nil {
		fmt.Println("Error decoding packet: ", err)
	}

	sDecode := pDecode.GetSample()
	fmt.Printf("Decoded sample = %+v\n", sDecode)

	sEvent := pDecode.GetEvent()
	fmt.Printf("Decoded event = %+v\n", sEvent)

}

// program output:
// sample: 27 bytes, packet: 29 bytes
// protobuf oneof overhead is 2 bytes per packet
// Decoded sample = id:"ET23B" index:2 value:2.1232 time:<seconds:1542820446 nanos:419989284 >
// Decoded event = <nil>
