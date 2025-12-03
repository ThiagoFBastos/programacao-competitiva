package main

import (
	"fmt"
	"math"
)

type Esfera struct {
	raio float64
}

func NovaEsfera(raio float64) *Esfera {
	return &Esfera{
		raio: raio,
	}
}

func (e *Esfera) volume() float64 {
	const PI = 3.14159
	return 4.0 / 3.0 * math.Pow(e.raio, 3) * PI
}

func main() {

	var raio float64

	fmt.Scan(&raio)

	esfera := NovaEsfera(raio)

	fmt.Printf("VOLUME = %.3f\n", esfera.volume())
}
