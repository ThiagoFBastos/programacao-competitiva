package main

import (
	"fmt"
)

func main() {
	var n1, n2, n3, n4 float64

	fmt.Scan(&n1, &n2, &n3, &n4)

	media := (2.0*n1 + 3.0*n2 + 4.0*n3 + n4) / 10.0

	fmt.Printf("Media: %.1f\n", media)

	if media < 5.0 {
		fmt.Println("Aluno reprovado.")
	} else if media < 7.0 {
		var n5 float64

		fmt.Println("Aluno em exame.")
		fmt.Scan(&n5)
		fmt.Printf("Nota do exame: %.1f\n", n5)

		media_final := (media + n5) / 2.0

		if media_final < 5.0 {
			fmt.Println("Aluno reprovado.")
		} else {
			fmt.Println("Aluno aprovado.")
		}

		fmt.Printf("Media final: %.1f\n", media_final)
	} else {
		fmt.Println("Aluno aprovado.")
	}
}
