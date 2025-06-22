use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn show(vec: &Vec<i32>, name: &str) {
    for (i, value) in vec.into_iter().enumerate() {
        println!("{}[{}] = {}", name, i, value);
    }
}

fn main() {

    let mut par = vec![];
    let mut impar = vec![];

    for _i in 1..=15 {
        let n = read_int();

        if n % 2 == 0 {
            par.push(n);
        } else {
            impar.push(n);
        }

        if impar.len() == 5 {
            show(&impar, "impar");
            impar.clear();
        } else if par.len() == 5 {
            show(&par, "par");
            par.clear();
        }
    }

    show(&impar, "impar");
    show(&par, "par");
}