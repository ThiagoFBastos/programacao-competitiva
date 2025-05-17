use std::io;

fn read_i32() -> i32 {
    let mut linha:String = String::new();

    io::stdin()
        .read_line(&mut linha)
        .expect("Falha ao tentar ler a linha");

    let valor: i32 = linha.trim()
                        .parse::<i32>()
                        .expect("Falha ao tentar interpretar como inteiro");

    return valor;
}

fn read_f64() -> f64 {
    let mut linha:String = String::new();

    io::stdin()
        .read_line(&mut linha)
        .expect("Falha ao tentar ler a linha");

    let valor: f64 = linha.trim()
                        .parse::<f64>()
                        .expect("Falha ao tentar interpretar como ponto flutuante");

    return valor;
}

fn main() {

    let km: i32 = read_i32();
    let litro: f64 = read_f64();

    let consumo = (km as f64) / litro;

    println!("{:.3} km/l", consumo);
}