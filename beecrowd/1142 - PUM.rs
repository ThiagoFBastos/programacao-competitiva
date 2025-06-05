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

    for i in 1..=4*n {
        if i % 4 == 0 {
            println!("PUM");
        } else {
            print!("{} ", i);
        }
    }
}