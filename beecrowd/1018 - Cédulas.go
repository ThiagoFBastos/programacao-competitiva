package main

import "fmt"

func main() {
	var dinheiro int32

	fmt.Scanf("%d", &dinheiro)

	cedulas := []int32{100, 50, 20, 10, 5, 2, 1}

	fmt.Printf("%d\n", dinheiro)

	for _, cedula := range cedulas {

		notas := dinheiro / cedula
		dinheiro %= cedula

		fmt.Printf("%d nota(s) de R$ %d,00\n", notas, cedula)
	}
}
