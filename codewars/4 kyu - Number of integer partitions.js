function partitions(n) {
    let part = new Array(n + 1).fill(0);
    part[0] = 1;
    for(let i = 1; i <= n; ++i)
        for(let j = 0; i + j <= n; ++j)
            part[i + j] += part[j];
    return part[n];
}