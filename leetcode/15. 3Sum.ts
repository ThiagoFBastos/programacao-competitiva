function threeSum(nums: number[]): number[][] {
    let triples: number[][] = [];

    nums.sort((a, b) => a - b);

    for(let i = 0; i < nums.length; ++i) {
        let hi: number = nums.length - 1;

        for(let j = i + 1; j < nums.length; ++j) {
            while(hi > j && -nums[i] - nums[j] < nums[hi]) --hi;

            if(hi > j && nums[i] + nums[j] + nums[hi] == 0) {
                if(i > 0 && nums[i - 1] == nums[i]) continue;
                else if(j - 1 > i && nums[j - 1] == nums[j]) continue;

                triples.push([nums[i], nums[j], nums[hi]]);
            }
        }
    }

    return triples;
};