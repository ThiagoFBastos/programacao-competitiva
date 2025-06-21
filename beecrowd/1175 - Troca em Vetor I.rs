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

    let mut vetor = [0; 20];

    for i in 0..=19 {
        vetor[i] = read_int();
    }

    vetor.reverse();

    for (i, valor) in vetor.iter().enumerate() {
        println!("N[{}] = {}", i, valor);
    }
}