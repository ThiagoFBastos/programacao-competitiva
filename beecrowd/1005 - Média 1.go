package main

import "fmt"

func main() {
	var nota1, nota2 float64

	fmt.Scan(&nota1)
	fmt.Scan(&nota2)

	media := (nota1*3.5 + nota2*7.5) / 11.0

	fmt.Printf("MEDIA = %.5f\n", media)
}
