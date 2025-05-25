use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
                .parse::<i32>()
                .expect("Falha ao ler inteiro");
}

fn read_3f64() -> (f64, f64, f64) {
     let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let valores: Vec<f64> = entrada.trim()
                                .split(" ")
                                .map(|x:&str| x.trim().parse::<f64>().expect("Falha ao ler ponto flutuante"))
                                .collect();

    return match valores.as_slice() {
        [a, b, c] => (*a, *b, *c),
        _ => panic!("Entrada com número incorreto de valoree")
    };
}

fn main() {

    let testes = read_int();

    for _i in 1..=testes {

        let (n1, n2, n3) = read_3f64();

        let media = (2.0 * n1 + 3.0 * n2 + 5.0 * n3) / 10.0;

        println!("{:.1}", media);
    }
}