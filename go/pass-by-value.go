package main

import "fmt"

func test(data []int) {
	data = append(data, 4)
	fmt.Println("data in test: ", data)
}

func main() {
	a := []int{1, 2, 3}
	fmt.Println("data before func: ", a)
	test(a)
	fmt.Println("data after func: ", a)
}

// program output:
// go run pass-by-value.go
// data before func:  [1 2 3]
// data in test:  [1 2 3 4]
// data after func:  [1 2 3]
