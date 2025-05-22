use std::io;

fn main() {

    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a entrada");

    let numero = entrada.trim()
                .parse::<usize>()
                .expect("Falha ao interpretar como inteiro");

    let meses: [&str; 12] = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];

    println!("{}", meses[numero - 1]);
}