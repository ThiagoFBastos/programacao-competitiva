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

    let mut tempo = read_i32();

    let anos = tempo / 365;

    tempo %= 365;

    let meses = tempo / 30;
    let dias = tempo % 30;

    println!("{} ano(s)\n{} mes(es)\n{} dia(s)", anos, meses, dias);
}