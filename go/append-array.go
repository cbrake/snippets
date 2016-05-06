package main

import (
	"fmt"
)

func main() {
	a := make([]int, 20)
	b := []int{1,2,3}

	a = append(a, b...)

	fmt.Println(a)

	copy(a[2:], b)

	fmt.Println(a)
}

