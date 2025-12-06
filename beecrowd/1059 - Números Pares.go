package main

import "fmt"

func main() {
	const N = 100

	for i := 2; i <= N; i += 2 {
		fmt.Printf("%d\n", i)
	}
}
