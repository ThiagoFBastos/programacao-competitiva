use std::io;

fn read_line(codigo: &mut i32, pecas: &mut i32, preco: &mut f64) {
    let mut line = String::new();

    io::stdin()
        .read_line(&mut line)
        .expect("Failed to read a line");

    let inputs: Vec<&str> = line.split(" ").collect();

    *codigo = inputs[0].trim()
                .parse::<i32>()
                .expect("Failed to parse a integer value");

    *pecas = inputs[1].trim()
        .parse::<i32>()
        .expect("Failed to parse a integer value");

    *preco = inputs[2].trim()
                .parse::<f64>()
                .expect("Failed to parse a floating point");
}

fn main() {

    let mut codigo1: i32 = 0;
    let mut pecas1: i32 = 0;
    let mut preco1: f64 = 0.0;

    let mut codigo2: i32 = 0;
    let mut pecas2: i32 = 0;
    let mut preco2: f64 = 0.0;

    read_line(&mut codigo1, &mut pecas1, &mut preco1);
    read_line(&mut codigo2, &mut pecas2, &mut preco2);

    let total: f64 = (pecas1 as f64) * preco1 + (pecas2 as f64) * preco2;

    println!("VALOR A PAGAR: R$ {:.2}", total);
}