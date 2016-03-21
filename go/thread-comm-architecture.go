package main

import (
	"fmt"
	"time"
)

type TypeA struct {
	value int
	desc string
}

type TypeB struct {
	value float32
	dest string
}

func FuncA(c chan interface{}) {
	for {
		c <- TypeA{3, "from TypeA"}
		time.Sleep(1 * time.Second)
	}
}

func FuncB(c chan interface{}) {
	for {
		c <- TypeB{10.2, "from TypeB"}
		time.Sleep(2 * time.Second)
	}
}


func main() {
	c := make(chan interface{}, 100)

	go FuncA(c)
	go FuncB(c)

	for {
		p := <-c
		switch p.(type) {
		case TypeA:
			fmt.Println("Received from A: ", p)
		case TypeB:
			fmt.Println("Received from B: ", p)
		}
	}
}

