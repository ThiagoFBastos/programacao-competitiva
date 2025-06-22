use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn main() {

    let t = read_int();

    for i in 0..=999 {
        println!("N[{}] = {}", i, i % t);
    }
}