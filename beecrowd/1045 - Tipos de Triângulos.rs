use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let mut lados: Vec<f64> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                    .collect();

    for _i in 0..=2 {
        for j in 0..=1 {
            if lados[j] < lados[j + 1] {
                let tmp = lados[j];
                lados[j] = lados[j + 1];
                lados[j + 1] = tmp;
            }
        }
    }

    let a = lados[0];
    let b = lados[1];
    let c = lados[2];

    if a >= b + c {
        println!("NAO FORMA TRIANGULO");
    } else {
        if a.powf(2.0) == b.powf(2.0) + c.powf(2.0) {
            println!("TRIANGULO RETANGULO");
        } else if a.powf(2.0) > b.powf(2.0) + c.powf(2.0) {
            println!("TRIANGULO OBTUSANGULO");
        } else {
            println!("TRIANGULO ACUTANGULO");
        }

        if a == b && b == c {
            println!("TRIANGULO EQUILATERO");
        } else if a == b || a == c || b == c {
            println!("TRIANGULO ISOSCELES");
        }
    }
}