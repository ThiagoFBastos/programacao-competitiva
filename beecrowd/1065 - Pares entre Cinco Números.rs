use std::io;

fn main() {

    let mut quantidade = i32::default();

    for _i in 1..=5 {
        let mut entrada = String::new();

        io::stdin()
            .read_line(&mut entrada)
            .expect("Falha ao ler string");

        let valor = entrada.trim()
                    .parse::<i32>()
                    .expect("Falha ao intrpretar como inteiro");

        if valor % 2 == 0 {
            quantidade += 1;
        }
    }

    println!("{} valores pares", quantidade);
}