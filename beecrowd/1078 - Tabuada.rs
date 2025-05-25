use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
                .parse::<i32>()
                .expect("Falha ao ler inteiro");
}

fn main() {

    let numero = read_int();

    for i in 1..=10 {
        println!("{} x {} = {}", i, numero, i * numero);
    }
}