use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao ler inteiro");
}

fn main() {

    loop {
        let senha = read_int();

        if senha == 2002 {
            println!("Acesso Permitido");
            break;
        }

        println!("Senha Invalida");
    }
}