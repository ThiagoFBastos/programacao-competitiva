package main

import (
	"fmt"
	"sort"
)

func main() {

	var nums [3]int

	for i := 0; i < 3; i++ {
		fmt.Scan(&nums[i])
	}

	copy_nums := nums

	sorted_nums := nums[:]

	sort.Ints(sorted_nums)

	for _, value := range sorted_nums {
		fmt.Printf("%d\n", value)
	}

	fmt.Println("")

	for _, value := range copy_nums {
		fmt.Printf("%d\n", value)
	}
}
