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

    let mut vetor: [i32; 10] = [0; 10];

    for i in 0..=9 {
        vetor[i] = read_int();

        if vetor[i] <= 0 {
            vetor[i] = 1;
        }

        println!("X[{}] = {}", i, vetor[i]);
    }
}