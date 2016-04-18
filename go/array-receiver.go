package main

import (
	"fmt"
	"strconv"
)

type TypeA struct {
	A string
}

type TypeB struct {
	A int
}

func (a TypeA) ToTypeB() TypeB {
	v,_ := strconv.Atoi(a.A)
	return TypeB{
		v,
	}
}

func (a []TypeA) ToTypeB() []TypeB {
	ret := make([]TypeB, 0)
	for _,v := range(a) {
		ret = append(ret, v.ToTypeB())
	}

	return ret
}

func main() {

	a := TypeA{"123"}

	fmt.Println("a: ", a)
	fmt.Println("conversion 1: ", a.ToTypeB())

	b := []TypeA{{"1"}, {"2"}, {"3"}}

	fmt.Println("b: ", b)
	fmt.Println("conversion 1: ", a.ToTypeB())
}

