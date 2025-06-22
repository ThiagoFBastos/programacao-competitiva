use std::io::stdin;

fn read_int() -> i32 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim().parse::<i32>().expect("Falha ao interpretar como inteiro");
}

fn read_vector() -> Vec<i32> {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    let numbers: Vec<i32> = input.trim()
                                .split(" ")
                                .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                                .collect();

    return numbers;
}

fn main() {

    let _n = read_int();
    
    let attacks = read_vector();

    let mut min_attack = attacks[0];
    let mut position = 0;

    for (i, a) in attacks.into_iter().enumerate() {
        if a < min_attack {
            min_attack = a;
            position = i;
        }
    }

    println!("{}", position + 1);
}