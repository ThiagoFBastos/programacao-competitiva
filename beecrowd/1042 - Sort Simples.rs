use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let numeros: Vec<i32> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como ponto flutuante"))
                    .collect();

    let mut numeros_ordenados = numeros.clone();
    numeros_ordenados.sort();

    for elemento in &numeros_ordenados {
        println!("{}", elemento);
    }

    println!("");

    for elemento in &numeros {
        println!("{}", elemento);
    }
}