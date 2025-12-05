package main

import "fmt"

func main() {
	var entrada float64

	fmt.Scan(&entrada)

	dinheiro := int32(entrada * 100)

	notas := []int32{10000, 5000, 2000, 1000, 500, 200}
	moedas := []int32{100, 50, 25, 10, 5, 1}

	fmt.Println("NOTAS:")

	for _, nota := range notas {
		quantidade := dinheiro / nota
		dinheiro %= nota

		fmt.Printf("%d nota(s) de R$ %d.00\n", quantidade, nota/100)
	}

	fmt.Println("MOEDAS:")

	for _, moeda := range moedas {
		quantidade := dinheiro / moeda
		dinheiro %= moeda

		fmt.Printf("%d moeda(s) de R$ %.2f\n", quantidade, float64(moeda)/100.0)
	}
}
