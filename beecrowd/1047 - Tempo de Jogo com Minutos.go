package main

import "fmt"

type Time struct {
	hours   int32
	minutes int32
}

func (t *Time) getElapsedTime(other *Time) *Time {
	const fullDayMinutes = 24 * 60
	var elapsedTime int32

	start := t.hours*60 + t.minutes
	end := other.hours*60 + other.minutes

	if start < end {
		elapsedTime = end - start
	} else {
		elapsedTime = fullDayMinutes - start + end
	}

	return &Time{
		hours:   elapsedTime / 60,
		minutes: elapsedTime % 60,
	}
}

func main() {
	var start, end Time

	fmt.Scan(&start.hours, &start.minutes, &end.hours, &end.minutes)

	time := start.getElapsedTime(&end)

	fmt.Printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", time.hours, time.minutes)
}
