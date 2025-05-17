use std::io;

fn read_i32() -> i32 {
    let mut linha = String::new();

    io::stdin()
        .read_line(&mut linha)
        .expect("Falha ao tentar ler a linha");

    let valor: i32 = linha.trim()
                        .parse::<i32>()
                        .expect("Falha ao interpretar como inteiro");

    return valor;
}

fn main() {

    let km: i32 = read_i32();

    let minutos = 2 * km;

    println!("{} minutos", minutos);
}