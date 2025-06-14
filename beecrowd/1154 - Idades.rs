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

    let mut quantidade = i32::default();
    let mut soma = i32::default();

    loop {
        let idade = read_int();

        if idade < 0 {
            break;
        }

        quantidade += 1;
        soma += idade;
    }

    let media = (soma as f64) / (quantidade as f64);

    println!("{:.2}", media);
}