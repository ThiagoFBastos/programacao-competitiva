use std::io::stdin;

fn read_int() -> i32 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim().parse::<i32>().expect("Falha ao interpretar como inteiro");
}

fn sum(x: i32, y: i32) -> i32 {
    return (x + y) * ((x - y).abs() + 1) / 2;
}

fn sum_13(x: i32, y: i32) -> i32 {
    let mut a = x;
    let mut b = y;

    if a > b {
        let tmp = a;
        a = b;
        b = tmp;
    }

    a = a + (13 - a % 13) % 13;
    b = b - b % 13;

    if a > b {
        return 0;
    }

    let n = (b - a) / 13 + 1;
 
    return n * (a + b) / 2;
}

fn main() {

    let x = read_int();
    let y = read_int();

    let ans = sum(x, y) - sum_13(x, y);

    println!("{}", ans);   
}