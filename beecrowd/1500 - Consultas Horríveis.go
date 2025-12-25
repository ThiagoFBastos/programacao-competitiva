package main

import (
	"bufio"
	"fmt"
	"os"
)

type SegTree struct {
	sum  []int64
	lazy []int64
	len  int
}

func NewSegTree(len int) *SegTree {
	return &SegTree{
		sum:  make([]int64, 4*len),
		lazy: make([]int64, 4*len),
		len:  len,
	}
}

func (st *SegTree) push(p int, len int) {
	if st.lazy[p] == 0 {
		return
	}

	mid := (len + 1) / 2
	st.sum[2*p] += st.lazy[p] * int64(mid)
	st.lazy[2*p] += st.lazy[p]

	mid = len / 2
	st.sum[2*p+1] += st.lazy[p] * int64(mid)
	st.lazy[2*p+1] += st.lazy[p]

	st.lazy[p] = 0
}

func (st *SegTree) query(lo, hi, l, r, p int) int64 {
	if hi < l || lo > r {
		return 0
	} else if lo >= l && hi <= r {
		return st.sum[p]
	}

	mid := (lo + hi) / 2

	st.push(p, hi-lo+1)

	p1 := st.query(lo, mid, l, r, 2*p)
	p2 := st.query(mid+1, hi, l, r, 2*p+1)

	return p1 + p2
}

func (st *SegTree) update(x int64, lo, hi, l, r, p int) {
	if hi < l || lo > r {
		return
	} else if lo >= l && hi <= r {
		st.lazy[p] += x
		st.sum[p] += x * int64(hi-lo+1)
		return
	}

	mid := (lo + hi) / 2

	st.push(p, hi-lo+1)

	st.update(x, lo, mid, l, r, 2*p)
	st.update(x, mid+1, hi, l, r, 2*p+1)

	st.sum[p] = st.sum[2*p] + st.sum[2*p+1]
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	var tc int

	fmt.Fscan(reader, &tc)

	for i := 0; i < tc; i++ {
		var n, q int

		fmt.Fscan(reader, &n, &q)

		st := NewSegTree(n)

		for j := 0; j < q; j++ {
			var t, l, r int
			var value int64

			fmt.Fscan(reader, &t, &l, &r)

			if t == 0 {
				fmt.Fscan(reader, &value)
				st.update(value, 0, n-1, l-1, r-1, 1)
			} else {
				result := st.query(0, n-1, l-1, r-1, 1)
				fmt.Fprintln(writer, result)
			}
		}
	}
}
