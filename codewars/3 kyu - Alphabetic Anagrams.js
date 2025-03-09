function listPosition(word) {
    let fat = n => {return n <= 1 ? 1 : n * fat(n - 1);};
    let permutations = s => {
        let frq = new Array(26).fill(0);
        for(let c of s) {
            let code = c.charCodeAt();
            ++frq[code - 'A'.charCodeAt()];    
        }
        let f = fat(s.length - 1), g = 1, ans = 0;
        for(let i = 0; i < 26; ++i) g *= fat(frq[i]);
        for(let i = 0; i < s[0].charCodeAt() - 'A'.charCodeAt(); ++i) if(frq[i] > 0) ans += f * frq[i] / g;
        return ans;
    };
    let rank = 1;
    for(let i = 0; i < word.length; ++i) rank += permutations(word.substr(i));
    return Math.round(rank);
}