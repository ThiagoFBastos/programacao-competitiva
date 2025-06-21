use std::io;

fn read_float() -> f64 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a string");

    return entrada.trim()
            .parse::<f64>()
            .expect("Falha ao interpretar como ponto flutuante");
}

fn main() {

    for i in 0..=99 {
        let valor = read_float();

        if valor <= 10.0 {
            println!("A[{}] = {:.1}", i, valor);
        }
    }
}