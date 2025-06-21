use std::io;

fn read_int() -> usize {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a string");

    return entrada.trim()
            .parse::<usize>()
            .expect("Falha ao interpretar como inteiro");
}

fn main() {

    let mut casos = read_int();

    let mut fib: [u64; 61] = [0; 61];

    fib[0] = 0;
    fib[1] = 1;

    for i in 2..=60 {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    while casos > 0 {
        let n = read_int();

        println!("Fib({}) = {}", n, fib[n]);

        casos -= 1;
    }
}