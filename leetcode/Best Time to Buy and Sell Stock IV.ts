function maxProfit(k: number, prices: number[]): number {
    const INF = 1e9;
    let dp: number[] = new Array<number>(2 * k + 1).fill(-INF);

    dp[0] = 0;

    for(let p of prices) {
        for(let i = 2 * k; i > 0; --i) {
            let priceSignal = i % 2 ? -p : p;
            dp[i] = Math.max(dp[i], dp[i - 1] + priceSignal);
        }
    }

    return dp.reduce((a, b) => Math.max(a, b), 0);
};