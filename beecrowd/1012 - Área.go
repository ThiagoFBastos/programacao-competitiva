package main

import (
	"fmt"
	"math"
)

type Area struct {
	a float64
	b float64
	c float64
}

func (area *Area) leitura() {
	fmt.Scan(&area.a, &area.b, &area.c)
}

func (area *Area) triangulo() float64 {
	return area.a * area.c / 2
}

func (area *Area) circulo() float64 {
	const PI = 3.14159

	return math.Pow(area.c, 2) * PI
}

func (area *Area) trapezio() float64 {
	return (area.a + area.b) * area.c / 2
}

func (area *Area) quadrado() float64 {
	return math.Pow(area.b, 2)
}

func (area *Area) retangulo() float64 {
	return area.a * area.b
}

func (area *Area) imprime() {
	fmt.Printf("TRIANGULO: %.3f\n", area.triangulo())
	fmt.Printf("CIRCULO: %.3f\n", area.circulo())
	fmt.Printf("TRAPEZIO: %.3f\n", area.trapezio())
	fmt.Printf("QUADRADO: %.3f\n", area.quadrado())
	fmt.Printf("RETANGULO: %.3f\n", area.retangulo())
}

func main() {

	var area Area

	area.leitura()
	area.imprime()
}
