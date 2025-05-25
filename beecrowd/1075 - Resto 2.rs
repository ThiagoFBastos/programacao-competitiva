use std::io;

fn read_int() -> usize {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
                    .parse::<usize>()
                    .expect("Falha ao ler como inteiro");
}

fn main() {

    let numero = read_int();
    
    if numero < 3 {
        return;
    }
    
    for i in (2..10001).step_by(numero) {
        println!("{}", i);
    }
}