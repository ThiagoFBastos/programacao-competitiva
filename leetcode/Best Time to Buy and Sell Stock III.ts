class Solution {
    #transations: number[][];

    constructor() {
        const INF = -1e9;

        this.#transations = [];
        for(let i = 0; i < 5; ++i)
            this.#transations[i] = [INF, INF];
    }

    static combine(a: Solution, b: Solution): Solution {
        let c = new Solution();

        for(let i = 1; i <= 4; ++i)
            for(let j = 0; j < 2; ++j)
                c.#transations[i][j] = Math.max(a.#transations[i][j], b.#transations[i][j]);

        for(let i = 1; i < 4; ++i) {
            for(let aSig = 0; aSig <= 1; ++aSig) {
                for(let j = 1; i + j <= 4; ++j) {
                    let bSig = (aSig + i) % 2;
                    c.#transations[i + j][aSig] = Math.max(c.#transations[i + j][aSig], a.#transations[i][aSig] + b.#transations[j][bSig]);
                }
            }
        }

        return c;
    }

    static fromOne(val: number): Solution {
        let solution = new Solution();
        solution.#transations[1][0] = -val;
        solution.#transations[1][1] = val;
        return solution;
    }

    get Value(): number {
        return Math.max(0, Math.max(this.#transations[4][0], this.#transations[2][0]));
    }
};

function MaxProfit(prices: number[], lo: number, hi: number): Solution {
    if(lo == hi) return Solution.fromOne(prices[lo]);

    const mid: number = (lo + hi) >> 1;

    let left: Solution = MaxProfit(prices, lo, mid);
    let right: Solution = MaxProfit(prices, mid + 1, hi);

    return Solution.combine(left, right);
};

function maxProfit(prices: number[]): number {
    return MaxProfit(prices, 0, prices.length - 1).Value;
};