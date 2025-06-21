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

fn sum_divisors(n: i32) -> i64 {
    let mut i = 1;
    let mut sum = i64::default();

    while i * i <= n {
        if n % i == 0 {
            sum += i as i64;
            if i * i != n {
                sum += (n / i) as i64;
            }
        }
        i += 1;
    }

    return sum;
}

fn is_perfect(n: i32) -> bool {
    return sum_divisors(n) == (2 * n) as i64;
}

fn main() {

    let casos = read_int();

    for _i in 1..=casos {
        let n = read_int();

        if is_perfect(n) {
            println!("{} eh perfeito", n);
        } else {
            println!("{} nao eh perfeito", n);
        }
    }
}