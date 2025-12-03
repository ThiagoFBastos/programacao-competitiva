package main

import "fmt"

func main() {
	var nome string
	var salario_fixo, vendas float64

	fmt.Scan(&nome)
	fmt.Scan(&salario_fixo)
	fmt.Scan((&vendas))

	salario := salario_fixo + 0.15*vendas

	fmt.Printf("TOTAL = R$ %.2f\n", salario)
}
