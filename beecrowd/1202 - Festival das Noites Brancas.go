package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
)

type Matrix struct {
	values [][]int32
	rows   int
	cols   int
}

func NewMatrix(rows, cols int) *Matrix {
	matrix := Matrix{
		values: make([][]int32, rows),
		rows:   rows,
		cols:   cols,
	}

	for i := 0; i < rows; i++ {
		matrix.values[i] = make([]int32, cols)
	}

	return &matrix
}

func (self *Matrix) multiply(other *Matrix, mod int32) (*Matrix, error) {
	if self.cols != other.rows {
		return nil, errors.New("matrizes incompatíveis")
	}

	result := NewMatrix(self.rows, other.cols)

	for i := 0; i < self.rows; i++ {
		for j := 0; j < other.cols; j++ {
			for k := 0; k < self.cols; k++ {
				result.values[i][j] = (result.values[i][j] + self.values[i][k]*other.values[k][j]) % mod
			}
		}
	}

	return result, nil
}

func (self *Matrix) pow(n string, mod int32) (*Matrix, error) {

	if self.rows != self.cols {
		return nil, errors.New("a matriz não é quadrada")
	}

	result := NewMatrix(self.rows, self.cols)
	self_copy := &*self

	for i := 0; i < self.rows; i++ {
		for j := 0; j < self.cols; j++ {
			if i == j {
				result.values[i][j] = 1
			}
		}
	}

	str := []rune(n)

	for i, j := 0, len(str)-1; i < j; i, j = i+1, j-1 {
		tmp := str[i]
		str[i] = str[j]
		str[j] = tmp
	}

	for _, ch := range str {
		if ch == '1' {
			result, _ = result.multiply(self_copy, mod)
		}

		self_copy, _ = self_copy.multiply(self_copy, mod)
	}

	return result, nil
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	const MOD = 1000

	var tc int

	fmt.Fscan(reader, &tc)

	for i := 0; i < tc; i++ {

		var exp string

		fmt.Fscan(reader, &exp)

		if exp == "1" || exp == "10" {
			fmt.Fprintln(writer, "001")
			continue
		}

		matrix := NewMatrix(2, 2)

		matrix.values[0][0] = 0
		matrix.values[0][1] = 1
		matrix.values[1][0] = 1
		matrix.values[1][1] = 1

		result, _ := matrix.pow(exp, MOD)

		inverse := NewMatrix(2, 2)

		inverse.values[0][0] = -1
		inverse.values[0][1] = 1
		inverse.values[1][0] = 1
		inverse.values[1][1] = 0

		result, _ = result.multiply(inverse, MOD)
		result, _ = result.multiply(inverse, MOD)

		fib := (result.values[1][0] + result.values[1][1] + MOD) % MOD

		fmt.Fprintf(writer, "%03d\n", fib)
	}
}
