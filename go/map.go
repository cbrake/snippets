package main

import "fmt"

type icon struct {
	on bool
}

func main() {
	iconMap := make(map[string]*icon)
	iconMap["arm"] = &icon{}
	iconMap["false"] = &icon{}

	iconMap["arm"].on = true

	for k, v := range iconMap {
		fmt.Println(k, v)
	}
}
