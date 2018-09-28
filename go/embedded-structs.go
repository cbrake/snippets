package main

import "fmt"

type A struct {
	FieldA1 string
	FieldA2 string
}

type B struct {
	A
	FieldA1 string
	FieldB  string
}

func main() {
	b := B{A{"1", "2"}, "3", "4"}

	fmt.Printf("b: %+v\n", b)

	fmt.Println("b.FieldA1: ", b.FieldA1)
	fmt.Println("b.A.FieldA1: ", b.A.FieldA1)

	// in this case since B does not have a Field2 field,
	// it looks in the embedded structs for the field.
	fmt.Println("b.FieldA2: ", b.FieldA2)
	fmt.Println("b.A.FieldA2: ", b.A.FieldA2)

	// does this also work for assignment?
	b.FieldA2 = "5"
	fmt.Println("b.FieldA2: ", b.FieldA2)
	fmt.Println("b.A.FieldA2: ", b.A.FieldA2)
	// yes it does :-)

	// however, this Field2 aliasing does not work for initialization
	// b2 := B{FieldA2: "6"}
	// we get the following error:
	// cannot use promoted field A.FieldA2 in struct literal of type B
}

/* program output
b: {A:{FieldA1:1 FieldA2:2} FieldA1:3 FieldB:4}
b.FieldA1:  3
b.A.FieldA1:  1
b.FieldA2:  2
b.A.FieldA2:  2
b.FieldA2:  5
b.A.FieldA2:  5
*/
