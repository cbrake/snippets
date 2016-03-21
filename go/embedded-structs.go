package main

import (
	"fmt"
)

type TypeA struct {
	fieldA1 string
	fieldA2 string
}

type TypeB struct {
	TypeA
	fieldB1 string
}

func main() {
	a := TypeA{"hi", "there"}
	b := TypeB{a, "cliff"}

	fmt.Println("a: ", a)
	fmt.Println("b: ", b)
	fmt.Println("b.fieldA1: ", b.fieldA1)
	fmt.Println("b.fieldA2: ", b.fieldA2)
	fmt.Println("b.TypeA.fieldA2: ", b.TypeA.fieldA2)
}

