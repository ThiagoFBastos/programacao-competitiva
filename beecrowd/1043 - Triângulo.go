package main

import "fmt"

func isTriangle(a, b, c float64) bool {
	return a < b+c && b < a+c && c < a+b
}

func trianglePerimeter(a, b, c float64) float64 {
	return a + b + c
}

func trapeziumArea(a, b, c float64) float64 {
	return (a + b) * c / 2.0
}

func main() {

	var a, b, c float64

	fmt.Scan(&a, &b, &c)

	if isTriangle(a, b, c) {
		fmt.Printf("Perimetro = %.1f\n", trianglePerimeter(a, b, c))
	} else {
		fmt.Printf("Area = %.1f\n", trapeziumArea(a, b, c))
	}
}
