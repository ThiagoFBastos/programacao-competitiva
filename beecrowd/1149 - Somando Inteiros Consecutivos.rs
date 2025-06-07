use std::io::stdin;

fn read_line() -> (i32, i32) {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    let mut values: Vec<i32> = input.trim()
                            .split_whitespace()
                            .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                            .collect();

    values = values.into_iter()
                .filter(|x| *x > 0)
                .collect();

    return match &values[0..2] {
        [a, b] => (*a, *b),
        _ => panic!("Número incorreto de parâmetros")
    };
}

fn sum(a0: i32, n: i32) -> i32 {
    return n * (2 * a0 + n - 1) / 2;
}

fn main() {

    let (a, n) = read_line();

    println!("{}", sum(a, n));
}