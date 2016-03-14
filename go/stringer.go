package main

import (
	"fmt"
)

type MyTest int

func (i MyTest) String() string {
	switch i {
	case 0:
		return "zero"
	case 1:
		return "one"
	case 2:
		return "two"
	case 3:
		return "three"
	case 4:
		return "four"
	case 5:
		return "five"
	default:
		return "unknown"
	}
}

func main() {
	var a MyTest = 5

	fmt.Println("MyTest: ", a)
	fmt.Printf("MyTest %v\n", a)

	// note the following does not work
	b := string(a)
	fmt.Println("b ", b)

	// but this does
	b = a.String()
	fmt.Println("b ", b)
}

