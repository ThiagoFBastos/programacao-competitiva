use std::io;

fn read_int() -> usize {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
            .parse::<usize>()
            .expect("Falha ao interpretar como inteiro");
}

fn read_vec_int() -> Vec<i32> {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let numeros: Vec<i32> = entrada.trim()
                    .split_whitespace()
                    .map(|x: &str| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                    .collect();

    return numeros;
}

fn main() {

    let n = read_int();
    
    let vec = read_vec_int();

    let mut min = vec[0];
    let mut pos = 0;

    for (i, value) in vec.into_iter().enumerate() {
        if value < min {
            min = value;
            pos = i;
        }
    }

    println!("Menor valor: {}", min);
    println!("Posicao: {}", pos);
}