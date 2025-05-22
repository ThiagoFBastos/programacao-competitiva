use std::io;

fn soma(a: i32, b: i32) -> i32 {
    let mut x = a;
    let mut y = b;

    if x > y {
        let tmp = x;
        x = y;
        y = tmp;
    }

    x += 1;
    y -= 1;

    if x % 2 == 0 {
        x += 1;
    }

    if y % 2 == 0 {
        y -= 1;
    }

    if x > y {
        return 0;
    }

    let n = (y - x + 2) / 2;

    return n * (x + y) / 2;
}

fn main() {

    let mut primeira_entrada = String::new();

    io::stdin()
        .read_line(&mut primeira_entrada)
        .expect("Falha ao ler uma string");

    let x = primeira_entrada.trim()
                .parse::<i32>()
                .expect("Falha ao ler como inteiro");

    let mut segunda_entrada = String::new();

    io::stdin()
        .read_line(&mut segunda_entrada)
        .expect("Falha ao ler uma string");

    let y = segunda_entrada.trim()
                .parse::<i32>()
                .expect("Falha ao ler como inteiro");

    println!("{}", soma(x, y));
}