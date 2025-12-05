package main

import "fmt"

type Time struct {
	horas    int32
	minutos  int32
	segundos int32
}

func getTime(segundos int32) Time {
	const horas2Segundos = 60 * 60
	const minutos2Segundos = 60

	var t Time

	t.horas = segundos / horas2Segundos
	segundos %= horas2Segundos
	t.minutos = segundos / minutos2Segundos
	segundos %= minutos2Segundos
	t.segundos = segundos

	return t
}

func (t Time) format() string {
	return fmt.Sprintf("%d:%d:%d", t.horas, t.minutos, t.segundos)
}

func main() {
	var segundos int32

	fmt.Scan(&segundos)

	t := getTime(segundos)

	fmt.Printf("%s\n", t.format())
}
