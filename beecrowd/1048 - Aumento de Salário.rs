use std::io;

fn read_float() -> f64 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
                    .parse::<f64>()
                    .expect("Falha ao ler como ponto flutuante");
}

fn main() {

    let salario = read_float();
    let mut percentual = i32::default();

    if salario <= 400.0 {
        percentual = 15;
    } else if salario <= 800.0 {
        percentual = 12;
    } else if salario <= 1200.0 {
        percentual = 10;
    } else if salario <= 2000.0 {
        percentual = 7;
    } else {
        percentual = 4;
    }

    let ganho = (percentual as f64) / 100.0 * salario;

    println!("Novo salario: {:.2}", salario + ganho);
    println!("Reajuste ganho: {:.2}", ganho);
    println!("Em percentual: {} %", percentual)
}