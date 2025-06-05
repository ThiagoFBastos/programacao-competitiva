use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao ler inteiro");
}

fn main() {

    let n = read_int();

    for i in 1..=n {
        println!("{} {} {}", i, i.pow(2), i.pow(3));
        println!("{} {} {}", i, i.pow(2) + 1, i.pow(3) + 1);
    }
}