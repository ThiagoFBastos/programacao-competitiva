function reverse(s) {
    let t = '';
    for(let i = s.length - 1; i >= 0; --i) t += s[i];
    return t;   
}

function countPalindromesLessOrEqual(n) {
    
    if(n < 10) return n + 1;

    let s = n.toString();
    let len = s.length, cnt = 10;
    
    for(let l = 1; 2 * l <= len; ++l) {
        let d = parseInt(s[l - 1]);
        cnt += 10 ** ((len - 2 * l + 1) / 2 | 0) * (d - (l == 1));
    }

    let mid = len / 2 | 0;

    let t = s.substring(0, mid) + (len % 2 ? s[mid] : '') + reverse(s.substring(0, mid));

    if(s >= t) ++cnt;

    if(len % 2 == 1) cnt += parseInt(s[mid]);

    for(let l = 2; l < len; ++l) cnt += 10 ** ((l - 1) / 2 | 0) * 9;

    return cnt;
}

function countPalindromes(a, b) {
    return a > b ? 0 : countPalindromesLessOrEqual(Math.floor(b)) - countPalindromesLessOrEqual(Math.ceil(a) - 1);
}