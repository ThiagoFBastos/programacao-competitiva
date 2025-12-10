package main

import "fmt"

func main() {
	var arr [6]float64

	positive := 0

	for i := 0; i < 6; i++ {
		fmt.Scan(&arr[i])

		if arr[i] > 0 {
			positive += 1
		}
	}

	fmt.Printf("%d valores positivos\n", positive)
}
