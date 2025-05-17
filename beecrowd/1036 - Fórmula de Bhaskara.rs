use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let valores: Vec<f64> = entrada.trim()
                                .split(" ")
                                .map(|x: &str| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                                .collect();

    let a = valores[0];
    let b = valores[1];
    let c = valores[2];

    let delta = b.powf(2.0) - 4.0 * a * c;

    if delta < 0.0 || a == 0.0 {
        println!("Impossivel calcular");
        return;
    }

    let r1 = (-b + delta.sqrt()) / (2.0 * a);
    let r2 = (-b - delta.sqrt()) / (2.0 * a);

    println!("R1 = {:.5}\nR2 = {:.5}", r1, r2);
}