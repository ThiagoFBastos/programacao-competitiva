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

fn is_prime(n: i32) -> bool {
    let mut i = 2;

    if n == 1 {
        return false;
    }

    while i * i <= n {
        if n % i == 0 {
            return false;
        }
        i += 1;
    }

    return true;
}

fn main() {

    let casos = read_int();

    for _i in 1..=casos {
        let numero = read_int();

        if is_prime(numero) {
            println!("{} eh primo", numero);
        } else {
            println!("{} nao eh primo", numero);
        }
    }
}