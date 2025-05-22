use std::io;

fn main() {

    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a entrada");

    let ddd = entrada.trim()
                .parse::<i32>()
                .expect("Falha ao interpretar como inteiro");

    match ddd {
        61 => println!("Brasilia"),
        71 => println!("Salvador"),
        11 => println!("Sao Paulo"),
        21 => println!("Rio de Janeiro"),
        32 => println!("Juiz de Fora"),
        19 => println!("Campinas"),
        27 => println!("Vitoria"),
        31 => println!("Belo Horizonte"),
        _  => println!("DDD nao cadastrado")
    }
}