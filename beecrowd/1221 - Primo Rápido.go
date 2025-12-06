package main

import "fmt"

func isPrime(num int) bool {
	if num == 1 {
		return false
	}

	for i := 2; i*i <= num; i++ {
		if num%i == 0 {
			return false
		}
	}

	return true
}

func main() {

	var tests int

	fmt.Scan(&tests)

	for c := 0; c < tests; c++ {
		var num int

		fmt.Scan(&num)

		if isPrime(num) {
			fmt.Println("Prime")
		} else {
			fmt.Println("Not Prime")
		}
	}
}
