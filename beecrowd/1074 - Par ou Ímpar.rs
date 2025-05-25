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

    let testes = read_int();

    for _i in 1..=testes {

        let numero = read_int();

        if numero == 0 {
            println!("NULL");
        } else if numero > 0 {
            if numero % 2 == 0 {
                println!("EVEN POSITIVE");
            } else {
                println!("ODD POSITIVE");
            }
        } else {
            if numero % 2 == 0 {
                println!("EVEN NEGATIVE");
            } else {
                println!("ODD NEGATIVE");
            }
        }
    }
}