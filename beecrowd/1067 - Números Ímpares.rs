use std::io;

fn main() {

    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let x: i32 = entrada.trim()
                    .parse::<i32>()
                    .expect("Falha ao interpretar como inteiro");

    for i in (1..(x+1)).step_by(2) {
        println!("{}", i);
    }
}