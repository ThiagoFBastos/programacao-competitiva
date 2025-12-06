package main

import (
	"fmt"
	"math"
	"sort"
)

func isTriangle(a, b, c float64) bool {
	return a < b+c && b < a+c && c < a+b
}

func triangleType(a, b, c float64) string {
	nums := []float64{a, b, c}

	sort.Float64s(nums)

	c = math.Pow(nums[0], 2)
	b = math.Pow(nums[1], 2)
	a = math.Pow(nums[2], 2)

	if a == b+c {
		return "TRIANGULO RETANGULO"
	} else if a > b+c {
		return "TRIANGULO OBTUSANGULO"
	}

	return "TRIANGULO ACUTANGULO"
}

func main() {
	var a, b, c float64

	fmt.Scan(&a, &b, &c)

	if !isTriangle(a, b, c) {
		fmt.Println("NAO FORMA TRIANGULO")
		return
	}

	fmt.Println(triangleType(a, b, c))

	if a == b && b == c {
		fmt.Println("TRIANGULO EQUILATERO")
	} else if a == b || a == c || b == c {
		fmt.Println("TRIANGULO ISOSCELES")
	}
}
