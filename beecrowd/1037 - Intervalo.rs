use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let numero: f64 = entrada.trim()
                        .parse::<f64>()
                        .expect("Falha ao interpretar como ponto flutuante");

    if numero < 0.0 {
        println!("Fora de intervalo");
    } else if numero <= 25.0 {
        println!("Intervalo [0,25]");
    } else if numero <= 50.0 {
        println!("Intervalo (25,50]");
    } else if numero <= 75.0 {
        println!("Intervalo (50,75]");
    } else if numero <= 100.0 {
        println!("Intervalo (75,100]");
    } else {
        println!("Fora de intervalo");
    }
}