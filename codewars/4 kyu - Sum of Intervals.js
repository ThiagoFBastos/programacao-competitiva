function sumIntervals(intervals) {
    intervals.sort((a, b) => a[0] - b[0]);
    let l = -(10 ** 9) - 1, r = -(10 ** 9) - 1, sum = 0;
    for(const [lo, hi] of intervals) {
        if(lo <= r) sum += Math.max(0, hi - r); 
        else sum += hi - lo;
        r = Math.max(hi, r);
    }
    return sum;
}