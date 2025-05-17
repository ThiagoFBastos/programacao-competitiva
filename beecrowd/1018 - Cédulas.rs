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

    let cedulas: [i32; 7] = [100, 50, 20, 10, 5, 2, 1];

    let mut dinheiro: i32 = read_i32();

    println!("{}", dinheiro);

    for cedula in &cedulas {

        let notas = dinheiro / (*cedula);
        println!("{} nota(s) de R$ {},00", notas, *cedula);
        dinheiro %= cedula;
    }
}