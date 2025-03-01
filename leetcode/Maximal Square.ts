class Sum2D<T> {
    #sum: Array<Array<number>>;

    constructor(matrix: T[][]) {
        const n = matrix.length;
        const m = matrix[0].length;

        this.#sum = [];

        for(let i = 0; i <= n; ++i)
            this.#sum[i] = new Array<number>(m + 1).fill(0);

        for(let i = 1; i <= n; ++i)
            for(let j = 1; j <= m; ++j)
                this.#sum[i][j] = this.#sum[i - 1][j] + this.#sum[i][j - 1] - this.#sum[i - 1][j - 1] + Number(matrix[i-1][j-1]);
    }

    query(x0: number, y0: number, x1: number, y1: number): number {
        return this.#sum[x1+1][y1+1] - this.#sum[x1+1][y0] - this.#sum[x0][y1+1] + this.#sum[x0][y0];
    }
};

function maximalSquare(matrix: string[][]): number {
    const n = matrix.length, m = matrix[0].length;
    let sum2d = new Sum2D<string>(matrix);
    let lo = 0, hi = Math.min(n, m) + 1;

    const HasSquare = (size: number): boolean => {
        for(let i = 0; i + size <= n; ++i) {
            for(let j = 0; j + size <= m; ++j) {
                let sum = sum2d.query(i, j, i + size - 1, j + size - 1);
                if(sum == size * size)
                    return true;
            }
        }
        return false;
    };

    while(lo < hi) {
        let mid: number = (lo + hi) >> 1;
        if(!HasSquare(mid))
            hi = mid;
        else
            lo = mid + 1;
    }

    return (hi - 1) * (hi - 1);
};