package main

import "fmt"

func main() {
	var tempo, velocidade float64

	fmt.Scan(&tempo, &velocidade)

	litros := tempo * velocidade / 12

	fmt.Printf("%.3f\n", litros)
}
