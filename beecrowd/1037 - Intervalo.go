package main

import (
	"fmt"
)

func main() {
	var num float64

	fmt.Scan(&num)

	if num < 0.0 {
		fmt.Println("Fora de intervalo")
	} else if num <= 25.0 {
		fmt.Println("Intervalo [0,25]")
	} else if num <= 50.0 {
		fmt.Println("Intervalo (25,50]")
	} else if num <= 75.0 {
		fmt.Println("Intervalo (50,75]")
	} else if num <= 100.0 {
		fmt.Println("Intervalo (75,100]")
	} else {
		fmt.Println("Fora de intervalo")
	}
}
