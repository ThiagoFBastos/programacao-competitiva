use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let numeros: Vec<i32> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                    .collect();

    let a = numeros[0]; 
    let b = numeros[1];

    if a % b == 0 || b % a == 0 {
        println!("Sao Multiplos");
    } else {
        println!("Nao sao Multiplos");
    }
}