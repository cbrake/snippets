package main

import (
	"fmt"
	"net"
)

func main() {
	fmt.Println("MDNS test")

	ips, _ := net.LookupIP("luna.local")
	for _, ip := range ips {
		fmt.Println("IP: ", ip)
	}
}

/* results

[cbrake@ceres go]$ CGO_ENABLED=1 go run mdns-test.go
MDNS test
IP:  fe80::7a02:43d1:6997:fe3


[cbrake@ceres go]$ CGO_ENABLED=0 go run mdns-test.go
MDNS test
IP:  10.0.0.118
IP:  fe80::7a02:43d1:6997:fe3

*/
