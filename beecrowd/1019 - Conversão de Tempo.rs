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

fn horario(tempo: i32) -> (i32, i32, i32) {
    let mut t = tempo;

    let horas = t / 3600;

    t %= 3600;

    let minutos = t / 60;

    t %= 60;

    let segundos = t;

    return (horas, minutos, segundos);
}

fn main() {

    let tempo = read_i32();

    let (horas, minutos, segundos) = horario(tempo);

    println!("{}:{}:{}", horas, minutos, segundos);
}