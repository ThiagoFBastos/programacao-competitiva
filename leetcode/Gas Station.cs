function canCompleteCircuit(gas: number[], cost: number[]): number {
    const n = gas.length, INF = 1e9;
    const suffix = new Array<number>(n + 1);
    const prefix = new Array<number>(n + 1);
    let sum = 0;

    for(let i = 0; i < n; ++i) {
        suffix[i] = sum;
        sum += gas[i] - cost[i];
    }

    if(sum < 0)
        return -1;

    suffix[n] = INF;
    prefix[0] = INF;
    for(let i = n - 1; i >= 0; --i)
        suffix[i] = Math.min(suffix[i], suffix[i + 1]);

    let others = 0;
    for(let i = 0; i < n; ++i) {
        let minGas = Math.min(prefix[i], suffix[i + 1]) + others;

        if(minGas >= 0)
            return i;

        prefix[i + 1] = Math.min(prefix[i], sum - others);
        others += cost[i] - gas[i];
    }

    return -1;
};