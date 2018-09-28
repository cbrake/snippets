package main

import "fmt"

func main() {
	fmt.Println("chan test")

	var c chan bool

	if c != nil {
		fmt.Println("closing channel")
		close(c)
	}

	c = make(chan bool, 1)

	if c != nil {
		fmt.Println("closing channel")
		close(c)
	}
}
