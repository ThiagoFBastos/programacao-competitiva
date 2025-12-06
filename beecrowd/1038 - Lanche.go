package main

import (
	"fmt"
)

func main() {
	var codigo, quantidade int32

	fmt.Scanf("%d%d", &codigo, &quantidade)

	preco_total := 0.0

	switch codigo {
	case 1:
		preco_total = float64(quantidade) * 4.0
	case 2:
		preco_total = float64(quantidade) * 4.5
	case 3:
		preco_total = float64(quantidade) * 5.0
	case 4:
		preco_total = float64(quantidade) * 2.0
	case 5:
		preco_total = float64(quantidade) * 1.5
	default:
		panic("código incorreto")
	}

	fmt.Printf("Total: R$ %.2f\n", preco_total)
}
