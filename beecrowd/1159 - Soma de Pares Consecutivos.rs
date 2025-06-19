use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a string");

    return entrada.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn sum_five_evens(n: i32) -> i32 {
    let mut a0 = n;

    if a0 % 2 != 0 {
        a0 += 1;
    }

    return 5 * (2 * a0 + 8) / 2;
}

fn main() {

    loop {
        let x = read_int();

        if x == 0 {
            break;
        }

        println!("{}", sum_five_evens(x));
    }
}