use std::io;

fn main() {

    let precos = [4.0, 4.5, 5.0, 2.0, 1.5];

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let valores: Vec<f64> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                    .collect();

    let item = valores[0] as usize;
    let quantidade = valores[1];

    println!("Total: R$ {:.2}", precos[item - 1] * quantidade);
}