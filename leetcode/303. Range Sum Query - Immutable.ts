class NumArray {
    private prefix: number[];

    constructor(nums: number[]) {
        const n = nums.length;
        this.prefix = new Array<number>(n + 1).fill(0);
        for(let i = 1; i <= n; ++i)
            this.prefix[i] = this.prefix[i - 1] + nums[i - 1];
    }

    sumRange(left: number, right: number): number {
        return this.prefix[right + 1] - this.prefix[left];
    }
}

/**
 * Your NumArray object will be instantiated and called as such:
 * var obj = new NumArray(nums)
 * var param_1 = obj.sumRange(left,right)
 */