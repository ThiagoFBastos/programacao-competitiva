use std::io;

fn read_float() -> f64 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
            .parse::<f64>()
            .expect("Falha ao interpretar como ponto flutuante");
}

fn main() {

    let mut x = read_float();

    for i in 0..=99 {
        println!("N[{}] = {:.4}", i, x);
        x = x / 2.0;
    }
}