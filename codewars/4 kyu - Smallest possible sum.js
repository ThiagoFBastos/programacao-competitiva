function gcd(a, b) {
    return b == 0 ? a : gcd(b, a % b);    
}

function solution(numbers) {
    let g = numbers[0];
    for(let x of numbers) g = gcd(g, x);
    return g * numbers.length;
} 