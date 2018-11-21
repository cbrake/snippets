// to generate protobuf go modules:
// go get -u github.com/golang/protobuf/protoc-gen-go
// protoc --go_out=. *.proto
package main

import (
	"encoding/csv"
	"encoding/json"
	"fmt"
	"os"
	"strconv"
	"time"

	"github.com/cbrake/snippets/go/packet"
	"github.com/golang/protobuf/ptypes"
)

func main() {
	packetCnt := []int{1, 5, 10, 100, 1000}

	csvWriter := csv.NewWriter(os.Stdout)

	csvWriter.Write([]string{
		"# samples",
		"JSON",
		"JSON.gz",
		"JSON.zip",
		"Gob",
		"Gob.gz",
		"Gob.zip",
		"PB",
		"PB.zip",
		"PB.zip % of JSON",
	})

	for _, cnt := range packetCnt {
		packets := packet.Samples{}
		for i := 0; i < cnt; i++ {
			ts, _ := ptypes.TimestampProto(time.Now())
			p := packet.Sample{
				Id:    "PywcZboRYH7JAuWa2",
				Type:  packet.Sample_ANALOG,
				Index: int32(i),
				Value: 2.1232 * float32(i),
				Time:  ts,
			}

			packets.Samples = append(packets.Samples, &p)
		}

		bJSON, err := json.Marshal(packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bJSONGzip, err := packet.EncodeJSONGzip(packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bJSONZlib, err := packet.EncodeJSONZlib(packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bGob, err := packet.EncodeGob(packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bGobGzip, err := packet.EncodeGobGzip(packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bGobZlib, err := packet.EncodeGobZlib(packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bPb, err := packet.EncodePb(&packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		bPbZlib, err := packet.EncodePbZlib(&packets)
		if err != nil {
			fmt.Println("Error encoding packet: ", err)
		}

		pbZipSavings := int(100 * float64(len(bPbZlib)) / float64(len(bJSON)))
		csvWriter.Write([]string{
			strconv.Itoa(cnt),
			strconv.Itoa(len(bJSON)),
			strconv.Itoa(len(bJSONGzip)),
			strconv.Itoa(len(bJSONZlib)),
			strconv.Itoa(len(bGob)),
			strconv.Itoa(len(bGobGzip)),
			strconv.Itoa(len(bGobZlib)),
			strconv.Itoa(len(bPb)),
			strconv.Itoa(len(bPbZlib)),
			strconv.Itoa(pbZipSavings),
		})
	}

	csvWriter.Flush()
}

// program output
// # Samples,JSON,JSON.gz,JSON.zip,Gob,Gob.gz,Gob.zip,PB,PB.zip,PB.zip % of JSON
// 1,88,113,101,435,278,266,35,48,54
// 5,488,185,173,624,336,324,203,101,20
// 10,997,246,234,860,407,395,413,157,15
// 100,10264,1304,1292,5119,1336,1324,4193,1019,9
// 1000,104393,12014,12002,49078,10194,10182,42865,9566,9
