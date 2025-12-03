package main

import "fmt"

func main() {
	var id, horas_trabalhadas int32
	var salario_por_hora float64

	fmt.Scan(&id)
	fmt.Scan(&horas_trabalhadas)
	fmt.Scan(&salario_por_hora)

	salario := float64(horas_trabalhadas) * salario_por_hora

	fmt.Printf("NUMBER = %d\n", id)
	fmt.Printf("SALARY = U$ %.2f\n", salario)
}
