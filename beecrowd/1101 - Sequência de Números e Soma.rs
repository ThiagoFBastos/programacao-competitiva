use std::io;
use std::cmp;

fn read_2ints() -> (i32, i32) {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let numeros: Vec<i32> = entrada.trim()
                                .split(" ")
                                .map(|x| x.trim().parse::<i32>().expect("Falha ao ler inteiro"))
                                .collect();
    return (numeros[0], numeros[1]);
}

fn main() {

    loop {
        let (a, b) = read_2ints();

        if a <= 0 || b <= 0 {
            break;
        }

        let l = cmp::min(a, b);
        let r = cmp::max(a, b);
        let mut soma = i64::default();

        for i in l..=r {
            print!("{} ", i);
            soma += i as i64;
        }

        println!("Sum={}", soma);
    }
}