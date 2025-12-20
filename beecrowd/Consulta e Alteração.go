package main

import (
	"bufio"
	"fmt"
	"os"
)

type SegTree struct {
	data []int64
	n    int
}

func gcd(a, b int64) int64 {
	if a < 0 {
		a *= -1
	}
	if b < 0 {
		b *= -1
	}
	if a == 0 {
		return b
	} else if a > b {
		return gcd(b, a)
	}
	return gcd(b%a, a)
}

func NewSegTree(initial []int64) *SegTree {

	n := len(initial)

	st := SegTree{
		data: make([]int64, 2*n),
		n:    n,
	}

	for i := 0; i < n; i++ {
		st.data[i+n] = initial[i]
	}

	for i := n - 1; i > 0; i-- {
		st.data[i] = gcd(st.data[2*i], st.data[2*i+1])
	}

	return &st
}

func (st *SegTree) query(l, r int) int64 {
	var result int64

	l += st.n
	r += st.n

	for l <= r {

		if l%2 == 1 {
			result = gcd(result, st.data[l])
			l += 1
		}

		if r%2 == 0 {
			result = gcd(result, st.data[r])
			r -= 1
		}

		l >>= 1
		r >>= 1
	}

	return result
}

func (st *SegTree) update(k int, x int64) {
	k += st.n
	st.data[k] += x

	for k > 1 {
		k >>= 1
		st.data[k] = gcd(st.data[2*k], st.data[2*k+1])
	}
}

type FenwinckTree struct {
	data []int64
	n    int
}

func NewFenwickTree(n int) *FenwinckTree {
	return &FenwinckTree{
		data: make([]int64, n+1),
		n:    n,
	}
}

func (ft *FenwinckTree) query(k int) int64 {
	var result int64

	for k > 0 {
		result += ft.data[k]
		k -= k & -k
	}

	return result
}

func (ft *FenwinckTree) update(k int, x int64) {

	for k <= ft.n {
		ft.data[k] += x
		k += k & -k
	}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	var n, q int

	fmt.Fscan(reader, &n, &q)

	nums := make([]int64, n)
	diff := make([]int64, n)
	ft := NewFenwickTree(n)

	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &nums[i])
		ft.update(i+1, nums[i])
		ft.update(i+2, -nums[i])
	}

	for i := 1; i < n; i++ {
		diff[i] = nums[i] - nums[i-1]
	}

	st := NewSegTree(diff)

	for i := 0; i < q; i++ {
		var t, l, r int
		var value int64

		fmt.Fscan(reader, &t, &l, &r)

		if t == 1 {
			fmt.Fscan(reader, &value)

			ft.update(l, value)
			ft.update(r+1, -value)

			st.update(l-1, value)

			if r < n {
				st.update(r, -value)
			}
		} else {
			result := ft.query(l)

			if l < r {
				result = gcd(result, st.query(l, r-1))
			}

			fmt.Fprintln(writer, result)
		}
	}
}
