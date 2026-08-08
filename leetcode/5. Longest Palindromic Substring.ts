function largestPalindrome(s: string): string {
    let l: number = 0, r: number = -1;
    let lo: number = 0, hi: number = -1;
    let n: number = s.length;
    let d1: number[] = new Array<number>(n).fill(1);
    let d2: number[] = new Array<number>(n).fill(0);

    for(let i = 0; i < n; ++i) {
        if(i <= r) {
            d1[i] = Math.min(d1[l + r - i], r - i + 1);
			d2[i] = Math.min(d2[l + r - i + 1], r - i + 1);
        }

        while(i + d1[i] < n && i - d1[i] >= 0 && s[i - d1[i]] == s[i + d1[i]]) ++d1[i];

        while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i - d2[i] - 1] == s[i + d2[i]]) ++d2[i];

        if(r < i + d2[i] - 1) l = i - d2[i], r = i + d2[i] - 1;
		if(r < i + d1[i] - 1) l = i - d1[i] + 1, r = i + d1[i] - 1;

        if(hi - lo + 1 < r - l + 1) {
            lo = l;
            hi = r;
        }
    }

    return s.substr(lo, hi - lo + 1);
}

function longestPalindrome(s: string): string {
    return largestPalindrome(s);
};