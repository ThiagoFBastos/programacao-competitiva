function maxSumOf(matrix) {
    let best = 0, n = matrix.length, m = matrix[0].length;

    let pre = new Array(n);

    for(let i = 0; i < n; ++i) {
        pre[i] = new Array(m + 1);
        pre[i][0] = 0;
        for(let j = 1; j <= m; ++j)
            pre[i][j] = pre[i][j - 1] + matrix[i][j - 1];
    }

    for(let l = 1; l <= m; ++l) {
        for(let j = 0; l + j <= m; ++j) {
            let sum = 0;
            for(let i = 0; i < n; ++i) {
                sum += pre[i][j + l] - pre[i][j];
                if(best < sum) best = sum;
                if(sum < 0) sum = 0;   
            }
        }
    }

    return best;
}