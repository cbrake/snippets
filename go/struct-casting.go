package main

import (
	"fmt"
)


type SubA []int
type SubB []int


type TypeA struct {
	A string
	B int
	C SubA
}

type TypeB struct {
	A string
	B int
	C SubA		// this works, but SubB does not
}

func main() {
	a := TypeA{"hi", 2, SubA{1,2,3}}
	b := TypeB(a)

	fmt.Println(a, b)
}

