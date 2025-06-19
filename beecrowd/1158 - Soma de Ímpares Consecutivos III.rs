use std::io::stdin;

fn read_int() -> i64 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim()
            .parse::<i64>()
            .expect("Falha ao interpretar como inteiro");
}

fn read_line() -> (i64, i64) {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    let values: Vec<i64> = input.trim()
                            .split_whitespace()
                            .map(|x| x.trim().parse::<i64>().expect("Falha ao interpretar como inteiro"))
                            .collect();

    return match values.as_slice() {
        [a, b] => (*a, *b),
        _ => panic!("Número incorreto de parâmetros")
    };
}

fn sum(a0: i64, r: i64, n: i64) -> i64 {
    return n * (2 * a0 + r * (n - 1)) / 2;
}

fn main() {

    let cases = read_int();

    for _i in 1..=cases {
        let (x, y) = read_line();

        println!("{}", sum(x + (!x & 1), 2, y));
    }
}