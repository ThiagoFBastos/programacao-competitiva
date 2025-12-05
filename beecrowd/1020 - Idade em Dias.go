package main

import "fmt"

func main() {
	var dias int32

	const anos2Dias = 365
	const meses2Dias = 30

	fmt.Scan(&dias)

	anos := dias / anos2Dias
	dias %= anos2Dias
	meses := dias / meses2Dias
	dias %= meses2Dias

	fmt.Printf("%d ano(s)\n", anos)
	fmt.Printf("%d mes(es)\n", meses)
	fmt.Printf("%d dia(s)\n", dias)
}
