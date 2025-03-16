function manacher(s) {
    let l = 0, r = -1, len = 0, n = s.length, from = -1, to = -1;
    let d1 = new Array(n).fill(1);
    let d2 = new Array(n).fill(0);

    for(let i = 0; i < n; ++i) {
        if(i <= r) {
            d1[i] = Math.min(d1[l + r - i], r - i + 1);
            d2[i] = Math.min(d2[l + r - i + 1], r - i + 1);
        }

        while(i + d1[i] < n && i - d1[i] >= 0 && s[i - d1[i]] == s[i + d1[i]]) ++d1[i];
		
		while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i - d2[i] - 1] == s[i + d2[i]]) ++d2[i];
		
		if(r < i + d2[i] - 1) {
            l = i - d2[i];
            r = i + d2[i] - 1;
        }

		if(r < i + d1[i] - 1) {
            l = i - d1[i] + 1;
            r = i + d1[i] - 1;
        }

        if(len < 2 * d1[i] - 1 || (len == 2 * d1[i] - 1 && i - d1[i] + 1 < from)) {
            len = 2 * d1[i] - 1;
            from = i - d1[i] + 1;
            to = i + d1[i] - 1;
        }

        if(len < 2 * d2[i] || (len == 2 * d2[i] && i - d2[i] < from)) {
            len = 2 * d2[i];
            from = i - d2[i];
            to = i + d2[i] - 1;
        }
    }

    return s.substr(from, to - from + 1);
}

function longest_palindrome(s) {
    return manacher(s);
}