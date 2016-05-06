package main

import (
	"fmt"
)

type TypeA struct {
	A int
	B TypeB
}

type TypeB struct {
	A int
	B string
}


func main() {
	a := TypeA{10, TypeB{20, "hi"}}
	b := TypeA{10, TypeB{20, "hi"}}
	c := TypeA{10, TypeB{20, "hi cliff"}}

	fmt.Println("a == b", a==b)
	fmt.Println("a == c", a==c)
}
