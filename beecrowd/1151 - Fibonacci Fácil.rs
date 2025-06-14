use std::io;

fn read_int() -> usize {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a string");

    return entrada.trim()
            .parse::<usize>()
            .expect("Falha ao interpretar como inteiro");
}

fn main() {

    let n = read_int();

    if n == 1 {
        println!("0");
        return;
    }

    let mut fib: Vec<i64> = vec![0, 1];

    for i in 2..=n-1 {
        fib.push(fib[i - 1] + fib[i - 2]);
    }

    for (i, value) in fib.into_iter().enumerate() {
        print!("{}", value);
        if i < n - 1 {
            print!(" ");
        } else {
            print!("\n");
        }
    }
}