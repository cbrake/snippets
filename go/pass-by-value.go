package main

import "fmt"

func test(data []int) {
	data = append(data, 4)
	fmt.Println("data in test: ", data)
}

func test2(data []int) {
	data[0] = 10
	fmt.Println("data in test2: ", data)
}

func main() {
	a := []int{1, 2, 3}
	fmt.Println("data before test(): ", a)
	test(a)
	fmt.Println("data after test(): ", a)
	test2(a)
	fmt.Println("data after test2(): ", a)
}

// program output:
// go run pass-by-value.go
// data before test():  [1 2 3]
// data in test:  [1 2 3 4]
// data after test():  [1 2 3]
// data in test2:  [10 2 3]
// data after test2():  [10 2 3]
