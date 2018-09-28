package main

import "fmt"

type Floats []float64

func (f *Floats) Push(v float64) {
	*f = append(*f, v)
}

func (f *Floats) Pop() float64 {
	ret := (*f)[0]
	*f = (*f)[1:]
	return ret
}

func (f *Floats) PopBack() float64 {
	ret := (*f)[len(*f)-1]
	*f = (*f)[:len(*f)-1]
	return ret
}

func main() {
	floats := Floats{1, 2}
	floats.Push(3)
	floats.Push(4)

	fmt.Println("floats: ", floats)
	fmt.Println("Pop: ", floats.Pop())
	fmt.Println("PopBack: ", floats.PopBack())
	fmt.Println("floats: ", floats)
}
