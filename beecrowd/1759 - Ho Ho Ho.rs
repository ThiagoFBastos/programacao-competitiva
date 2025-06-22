use std::io::stdin;

fn read_int() -> i32 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn main() {

    let n = read_int();

    let mut answer = String::new();

    for i in 1..=n {
        answer.push_str("Ho");
        answer.push(if i < n { ' ' } else { '!' });
    }

    println!("{}", answer);
}