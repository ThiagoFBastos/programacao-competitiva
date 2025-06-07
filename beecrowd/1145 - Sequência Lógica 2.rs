use std::io;

fn read_line() -> (i32, i32) {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a string");

    let numeros: Vec<i32> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                    .collect();

    return match numeros.as_slice() {
        [a, b] => (*a, *b),
        _ => panic!("Quantidade de argumentos inválida")
    };
}

fn main() {

    let (x, y) = read_line();

    for i in 1..=y {
        print!("{}", i);
        if i % x == 0 {
            print!("\n");
        } else {
            print!(" ");
        }
    }
}