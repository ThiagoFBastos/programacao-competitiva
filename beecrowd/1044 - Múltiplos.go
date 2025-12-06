package main

import "fmt"

func main() {
	var num1, num2 int32

	fmt.Scan(&num1, &num2)

	if num1%num2 == 0 || num2%num1 == 0 {
		fmt.Println("Sao Multiplos")
	} else {
		fmt.Println("Nao sao Multiplos")
	}
}
