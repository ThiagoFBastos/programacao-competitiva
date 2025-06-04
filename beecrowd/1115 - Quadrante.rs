use std::io;

fn read_line() -> (i32, i32) {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let numeros: Vec<i32> = entrada.trim()
                            .split(" ")
                            .map(|x| x.trim().parse::<i32>().expect("Falha ao ler inteiro"))
                            .collect();

    return match numeros.as_slice() {
        [a, b] => (*a, *b),
        _ => panic!("Número de elementos incorretos")
    };
}

fn main() {

    loop {
        let (x, y) = read_line();

        if x == 0 || y == 0 {
            break;
        } else if x > 0 && y > 0 {
            println!("primeiro");
        } else if x < 0 && y > 0 {
            println!("segundo");
        } else if x < 0 && y < 0 {
            println!("terceiro");
        } else {
            println!("quarto");
        }
    }
}