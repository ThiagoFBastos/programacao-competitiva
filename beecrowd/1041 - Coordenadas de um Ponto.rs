use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let valores: Vec<f64> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                    .collect();

    let x = valores[0];
    let y = valores[1];

    if x > 0.0 && y > 0.0 {
        println!("Q1");
    } else if x < 0.0 && y > 0.0 {
        println!("Q2");
    } else if x < 0.0 && y < 0.0 {
        println!("Q3");
    } else if x > 0.0 && y < 0.0 {
        println!("Q4");
    } else if x == 0.0 && y == 0.0 {
        println!("Origem");
    } else if y == 0.0 {
        println!("Eixo X");
    } else {
        println!("Eixo Y");
    }
}