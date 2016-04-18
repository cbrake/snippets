package main

import (
	"fmt"
	"encoding/json"
)

type TypeA struct {
	FieldA string `json:"fieldA,omitempty"`
	FieldB float32 `json:"fieldB,omitempty"`
}

func main() {
	a := TypeA{"test", 23.5}
	m, _ := json.Marshal(a)
	fmt.Println(string(m))
	a = TypeA{"", 0}
	m, _ = json.Marshal(a)
	fmt.Println(string(m))
}


