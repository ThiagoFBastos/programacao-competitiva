function smaller(arr) {
    const n = arr.length;

    let bit = new Array(n + 1).fill(0);
    let res = new Array(n);

    let upd = (k, x) => {for(++k; k <= n; k += k & -k) bit[k] += x;};
    let query = k => {let ans = 0; for(++k; k > 0; k -= k & -k) ans += bit[k]; return ans;};
    let lower_bound = (arr, v) => {
        let lo = 0, hi = arr.length - 1;
        while(lo < hi) {
            let mid = (lo + hi) >> 1;
            if(arr[mid] >= v) hi = mid;
            else lo = mid + 1;
        }  
        return hi;
    };

    let sorted_arr = arr.map(x => x);
    
    sorted_arr.sort((a, b) => a - b);

    for(let i = n - 1; i >= 0; --i) {
        let x = lower_bound(sorted_arr, arr[i]);
        res[i] = query(x - 1);
        upd(x, 1);
    }

    return res;
}