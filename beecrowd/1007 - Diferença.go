package main

import "fmt"

func main() {
	var nums [4]int32

	for i := 0; i < 4; i++ {
		fmt.Scan(&nums[i])
	}

	diff := nums[0]*nums[1] - nums[2]*nums[3]

	fmt.Printf("DIFERENCA = %d\n", diff)
}
