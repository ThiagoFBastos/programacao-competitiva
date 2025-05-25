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

    let mut maior = i32::default();
    let mut posicao = i32::default();

    for i in 1..=100 {
        let numero = read_int();

        if numero > maior {
            maior = numero;
            posicao = i;
        }
    }

    println!("{}\n{}", maior, posicao);
}