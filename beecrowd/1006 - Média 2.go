package main

import "fmt"

func main() {
	var nota1, nota2, nota3 float64

	fmt.Scan(&nota1)
	fmt.Scan(&nota2)
	fmt.Scan(&nota3)

	media := (nota1*2.0 + nota2*3.0 + nota3*5.0) / 10.0

	fmt.Printf("MEDIA = %.1f\n", media)
}
