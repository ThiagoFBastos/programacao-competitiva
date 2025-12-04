package main

import (
	"fmt"
	"math"
)

type Point struct {
	x float64
	y float64
}

func (p *Point) read() {
	fmt.Scan(&p.x, &p.y)
}

func (p *Point) distance(other *Point) float64 {
	return math.Sqrt(math.Pow(p.x-other.x, 2) + math.Pow(p.y-other.y, 2))
}

func main() {
	var p1, p2 Point

	p1.read()
	p2.read()

	fmt.Printf("%.4f\n", p1.distance(&p2))
}
