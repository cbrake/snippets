package main

import (
	"fmt"
)

type A struct {
	Var1 int
	Var2 int
}

func main() {
	a := A{1,2}
	b := a

	fmt.Println("a: ", a)

	b.Var1 = 3

	fmt.Println("a: ", a)
	fmt.Println("b: ", b)
}


// outputs:
//a:  {1 2}
//a:  {1 2}
//b:  {3 2}
// conclusion, struct copies are full copies, not ref copies


