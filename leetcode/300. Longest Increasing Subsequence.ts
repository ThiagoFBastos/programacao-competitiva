function lower_bound(arr: number[], value: number): number {
    let lo: number = 0, hi: number = arr.length - 1;

    while(lo < hi) {
        let mid = (lo + hi) / 2 | 0;

        if(arr[mid] >= value)
            hi = mid;
        else
            lo = mid + 1;
    }

    return hi;
}

function lengthOfLIS(nums: number[]): number {
    let n: number = nums.length;
    let sequence = new Array<number>(n).fill(Number.MAX_SAFE_INTEGER);
    let len: number = 0;

    for(let val of nums) {
        let k = lower_bound(sequence, val);

        if(len < k + 1)
            len = k + 1;

        sequence[k] = val;
    }

    return len;
};