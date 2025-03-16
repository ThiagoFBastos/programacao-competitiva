function nextBigger(n){
    let digits = new Array(10).fill(0);
    let s = n.toString(), t = '';
    for(let c of s) ++digits[c.charCodeAt() - '0'.charCodeAt()];    
    for(let i = 0; i < s.length; ++i) {
        let found = false; 
        for(let c = 0; c <= 9; ++c) {
            if(digits[c] == 0 || (i == 0 && c == 0)) continue;
            let tmp = t + c.toString();
            --digits[c];
            for(let k = 9; k >= 0; --k)
                for(let j = 0; j < digits[k]; ++j)
                    tmp += k.toString();
            if(tmp > s) {
                t += c.toString();
                found = true;
                break;
            }
            ++digits[c];
        }
        if(!found) return -1;
    }
    return parseInt(t);
}