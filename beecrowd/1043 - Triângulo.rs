use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let numeros: Vec<f64> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                    .collect();

    let a = numeros[0];
    let b = numeros[1];
    let c = numeros[2];

    if a >= b + c || b >= a + c || c >= a + b {
        println!("Area = {:.1}", (a + b) * c / 2.0);
    } else {
        println!("Perimetro = {:.1}", a + b + c);
    }
}