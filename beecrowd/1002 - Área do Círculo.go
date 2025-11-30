package main

import (
	"fmt"
)

func circle_area(r float64) float64 {
	const PI = 3.14159
	return r * r * PI
}

func main() {
	var r float64

	fmt.Scan(&r)

	fmt.Printf("A=%.4f\n", circle_area(r))
}
