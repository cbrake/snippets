package main

import (
	"fmt"

	"github.com/jinzhu/copier"
)

type state struct {
	Description string
	data        []float64
	attributes  map[string]string
}

func main() {

	s := state{
		Description: "hi there",
		data:        []float64{1, 2, 3, 4, 5},
		attributes: map[string]string{
			"att1": "got it",
			"att2": "hey there",
		},
	}

	sCopy := state{}
	err := copier.Copy(&sCopy, &s)
	if err != nil {
		fmt.Println("Error copying state: ", err)
	}

	s.data[0] = 100
	s.attributes["att1"] = "nice day"

	fmt.Printf("s: %+v\n", s)
	fmt.Printf("sCopy: %+v\n", s)
}
