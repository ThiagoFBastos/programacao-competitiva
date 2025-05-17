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

   let horas: i32 = read_i32();
   let velocidade: i32 = read_i32();

   let km = horas * velocidade;

   let litros = (km as f64) / 12.0;

   println!("{:.3}", litros)
}