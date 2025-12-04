package main

import "fmt"

func main() {
	var distancia int32

	fmt.Scan(&distancia)

	tempo := distancia * 2

	fmt.Printf("%d minutos\n", tempo)
}
