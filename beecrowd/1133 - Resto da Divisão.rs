use std::io;
use std::cmp;

fn read_int() -> usize {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<usize>().expect("Falha ao ler inteiro");
}

fn main() {

    let a = read_int();
    let b = read_int();

    let l = cmp::min(a, b) + 1;
    let r = cmp::max(a, b) - 1;

    for i in l..=r {
        if i % 5 == 2 || i % 5 == 3 {
            println!("{}", i);
        }
    }
}