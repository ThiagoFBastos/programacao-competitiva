package main

import (
	"bufio"
	"fmt"
	"os"
)

type FenwickTree struct {
	sum []int64
	n   int
}

func NewFenwickTree(n int) *FenwickTree {
	return &FenwickTree{
		sum: make([]int64, n+1),
		n:   n,
	}
}

func (ft *FenwickTree) query(k int) int64 {
	var result int64

	for k > 0 {
		result += ft.sum[k]
		k -= k & -k
	}

	return result
}

func (ft *FenwickTree) update(k int, value int64) {
	for k <= ft.n {
		ft.sum[k] += value
		k += k & -k
	}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	var n int
	var answer int64

	fmt.Fscan(reader, &n)

	ft := []FenwickTree{*NewFenwickTree(n), *NewFenwickTree(n)}

	for i := 0; i < n; i++ {
		var value int

		fmt.Fscan(reader, &value)

		answer += ft[1].query(n) - ft[1].query(value)
		ft[1].update(value, int64(i)-ft[0].query(value))
		ft[0].update(value, 1)
	}

	fmt.Fprintln(writer, answer)
}
