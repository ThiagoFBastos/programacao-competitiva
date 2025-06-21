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

fn main() {

    let mut v = read_int();

    for i in 0..=9 {
        println!("N[{}] = {}", i, v);
        v = 2 * v;
    }
}