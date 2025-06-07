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

fn main() {

    loop {
        let x = read_int();

        if x == 0 {
            break;
        }

        for i in 1..=x {
            print!("{}", i);
            if i < x {
                print!(" ");
            } else {
                print!("\n");
            }
        }
    }
}