package main

import "fmt"

func main() {
	var h1, h2 int32

	fmt.Scan(&h1, &h2)

	var time int32

	if h1 < h2 {
		time = h2 - h1
	} else {
		time = 24 - h1 + h2
	}

	fmt.Printf("O JOGO DUROU %d HORA(S)\n", time)
}
