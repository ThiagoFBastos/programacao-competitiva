package main

import (
	"fmt"
)

func main() {
	var x, y float64

	fmt.Scanf("%f%f", &x, &y)

	if x > 0.0 && y > 0.0 {
		fmt.Println("Q1")
	} else if x < 0.0 && y > 0.0 {
		fmt.Println("Q2")
	} else if x < 0.0 && y < 0.0 {
		fmt.Println("Q3")
	} else if x > 0.0 && y < 0.0 {
		fmt.Println("Q4")
	} else if x == 0.0 && y == 0.0 {
		fmt.Println("Origem")
	} else if x == 0.0 {
		fmt.Println("Eixo Y")
	} else {
		fmt.Println("Eixo X")
	}
}
