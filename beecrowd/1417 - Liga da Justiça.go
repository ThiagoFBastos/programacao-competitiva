package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

type Vertex struct {
	vertex int
	degree int
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	defer writer.Flush()

	for {
		var n, m int

		fmt.Fscan(reader, &n, &m)

		if n+m == 0 {
			break
		}

		vertexes := make([]Vertex, n)
		prefix := make([]int, n+1)

		for i := 0; i < n; i++ {
			vertexes[i].vertex = i
			vertexes[i].degree = 0
		}

		for i := 0; i < m; i++ {
			var u, v int

			fmt.Fscan(reader, &u, &v)

			vertexes[u-1].degree += 1
			vertexes[v-1].degree += 1
		}

		vertexes_slice := vertexes[:]

		sort.Slice(vertexes_slice, func(i, j int) bool {
			return vertexes_slice[i].degree > vertexes_slice[j].degree
		})

		prefix[0] = 0
		for i := 1; i <= n; i++ {
			prefix[i] = prefix[i-1] + vertexes_slice[i-1].degree
		}

		flag := false

		for i := 1; i <= n; i++ {
			flag = flag || prefix[i] == i*(i-1)+prefix[n]-prefix[i]
		}

		if flag {
			fmt.Fprintln(writer, "Y")
		} else {
			fmt.Fprintln(writer, "N")
		}
	}
}
