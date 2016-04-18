package main

import (
	"fmt"
	"time"
)

func shortDelay(exp chan bool) {
	time.Sleep(500 * time.Millisecond)
	exp <- true
}

func main() {
	make(c, bool chan)

	select 
}
