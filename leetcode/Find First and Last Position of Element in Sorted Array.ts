function lowerBound(nums: number[], target: number): number {
    let l = 0, r = nums.length;
    while(l < r) {
        const m = (l + r) / 2 | 0;
        if(nums[m] >= target)
            r = m;
        else
            l = m + 1;
    }
    return r;
}

function searchRange(nums: number[], target: number): number[] {
    let low = lowerBound(nums, target);

    if(low >= nums.length || nums[low] != target)
        return [-1, -1];

    let high = lowerBound(nums, target + 1);

    return [low, high - 1];
};