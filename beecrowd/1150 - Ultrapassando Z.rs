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

    let x = read_int();
    let mut z = i32::default();

    loop {
        z = read_int();

        if z > x {
            break;
        }
    }

    let mut n = 0;
    let mut sum = i32::default();

    while sum <= z {
        sum += x + n;
        n += 1;
    }

    println!("{}", n);
}