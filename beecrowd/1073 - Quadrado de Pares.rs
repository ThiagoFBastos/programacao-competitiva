use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao interpretar como inteiro");
}

fn main() {

    let n = read_int();

    for i in (2..(n + 1)).step_by(2) {
        println!("{}^2 = {}", i, i * i);
    }
}