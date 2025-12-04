package main

import (
	"fmt"
)

func main() {

	var distancia, consumo float64

	fmt.Scan(&distancia, &consumo)

	consumo_medio := distancia / consumo

	fmt.Printf("%.3f km/l\n", consumo_medio)
}
