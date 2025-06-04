use std::io;

fn read_int() -> usize {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<usize>().expect("Falha ao ler inteiro");
}

fn read_line() -> (f64, f64) {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let numeros: Vec<f64> = entrada.trim()
                            .split(" ")
                            .map(|x| x.trim().parse::<f64>().expect("Falha ao ler ponto flutuante"))
                            .collect();

    return match numeros.as_slice() {
        [a, b] => (*a, *b),
        _ => panic!("Número de elementos incorretos")
    };
}

fn main() {

    let casos = read_int();

    for _i in 1..=casos {
        let (x, y) = read_line();

        if y == 0.0 {
            println!("divisao impossivel");
            continue;
        }

        println!("{:.1}", x / y);
    }
}