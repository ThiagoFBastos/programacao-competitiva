/**
 Do not return anything, modify nums1 in-place instead.
 */

function copy(dest: number[], src: number[], n: number): void {
    for(let i = 0; i < n; ++i)
        dest[i] = src[i];
}

function merge(nums1: number[], m: number, nums2: number[], n: number): void {
    let nums3 = new Array<number>(m);
    let i = 0, j = 0, k = 0;

    copy(nums3, nums1, m);

    while(i < n && j < m) nums1[k++] = nums2[i] < nums3[j] ? nums2[i++] : nums3[j++];
    for(; i < n; ++i) nums1[k++] = nums2[i];
    for(; j < m; ++j) nums1[k++] = nums3[j];
};