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

    let numero = read_int();

    let mut divisores = vec![];

    let mut i = 1;

    while i * i <= numero {
        if numero % i == 0 {
            divisores.push(i);
            if i * i != numero {
                divisores.push(numero / i);
            }
        }
        i += 1;
    }

    divisores.sort();

    for i in divisores.iter() {
        println!("{}", i);
    }
}