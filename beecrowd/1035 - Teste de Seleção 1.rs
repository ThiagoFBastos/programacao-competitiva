use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let valores: Vec<i32> = entrada.trim()
                                .split(" ")
                                .map(|x: &str| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                                .collect();

    let a = valores[0];
    let b = valores[1];
    let c = valores[2];
    let d = valores[3];

    if b > c && d > a && c + d > a + b && c > 0 && d > 0 && a % 2 == 0 {
        println!("Valores aceitos");
    } else {
        println!("Valores nao aceitos");
    }
}