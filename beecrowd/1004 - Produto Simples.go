package main

import "fmt"

func main() {
	var num1, num2 int64

	fmt.Scan(&num1)
	fmt.Scan(&num2)

	prod := num1 * num2

	fmt.Printf("PROD = %d\n", prod)
}
