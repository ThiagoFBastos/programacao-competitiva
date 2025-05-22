use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao interpretar como inteiro");
}

fn main() {

    let mut n = read_int();

    if n % 2 == 0 {
        n += 1;
    }

    for i in 0..=5 {
        println!("{}", n + 2 * i);
    }
}