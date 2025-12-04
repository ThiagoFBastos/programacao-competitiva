package main

import (
	"fmt"
)

func abs(a int32) int32 {
	if a < 0 {
		return -a
	}

	return a
}

func max(a, b int32) int32 {
	return (a + b + abs(a-b)) / 2
}

func main() {

	var a, b, c int32

	fmt.Scan(&a, &b, &c)

	resultado := max(max(a, b), c)

	fmt.Printf("%d eh o maior\n", resultado)
}
