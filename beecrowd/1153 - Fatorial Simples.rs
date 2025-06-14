use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a string");

    return entrada.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn fatorial(n: i64) -> i64 {
    if n <= 1 {
        return 1;
    }

    return n * fatorial(n - 1);
}

fn main() {

    let n = read_int();

    println!("{}", fatorial(n as i64));
}