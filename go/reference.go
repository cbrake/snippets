package main

import "fmt"

type abc struct {
	A string
	B int
}

func main() {
	a := 10
	fmt.Println(&a)
	a = 20
	fmt.Println(&a)

	c := abc{"hi", 20}
	fmt.Println(&c)
	c = abc{"there", 40}
	fmt.Println(&c)
}
