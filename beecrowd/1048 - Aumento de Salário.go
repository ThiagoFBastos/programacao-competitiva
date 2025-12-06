package main

import "fmt"

func getReajuste(salario float64) int32 {
	if salario <= 400.0 {
		return 15
	} else if salario <= 800.0 {
		return 12
	} else if salario <= 1200.0 {
		return 10
	} else if salario <= 2000.0 {
		return 7
	}
	return 4
}

func main() {
	var salario float64

	fmt.Scan(&salario)

	percentual := getReajuste(salario)
	reajuste := salario * float64(percentual) / 100.0
	novo_salario := salario + reajuste

	fmt.Printf("Novo salario: %.2f\n", novo_salario)
	fmt.Printf("Reajuste ganho: %.2f\n", reajuste)
	fmt.Printf("Em percentual: %d %%\n", percentual)
}
