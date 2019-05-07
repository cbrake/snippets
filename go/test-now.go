package main

import (
	"fmt"
	"time"

	"github.com/jinzhu/now"
)

var layoutDateTime = "2006-01-02 15:04"
var layoutTime = "15:04"
var layoutDate = "2006-01-02"

func parseTime(t string) (time.Time, error) {
	t = time.Now().Format(layoutDate) + " " + t
	return time.Parse(layoutDateTime, t)
}

func main() {
	fmt.Println(now.Parse("12:30"))

	// ref layout string: Mon Jan 2 15:04:05 MST 2006
	//utc, _ := time.LoadLocation("UTC")
	fmt.Println(time.Parse(layoutDateTime, "2019-05-07 12:21"))
	fmt.Println(parseTime("12:21"))
}
