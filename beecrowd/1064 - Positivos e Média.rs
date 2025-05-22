use std::io;

fn main() {

    let mut soma = f64::default();
    let mut quantidade = i32::default();

    for _i in 1..=6 {
        let mut entrada = String::new();

        io::stdin()
            .read_line(&mut entrada)
            .expect("Falha ao ler string");

        let valor = entrada.trim()
                    .parse::<f64>()
                    .expect("Falha ao intrpretar como ponto flutuante");

        if valor > 0.0 {
            soma += valor;
            quantidade += 1;
        }
    }

    let media = soma / (quantidade as f64);

    println!("{} valores positivos", quantidade);
    println!("{:.1}", media);
}