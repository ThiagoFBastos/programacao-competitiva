use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let tempos: Vec<i32> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                    .collect();

    let inicio = tempos[0];
    let fim = tempos[1];
    let mut horas: i32 = i32::default();

    if inicio < fim {
        horas = fim - inicio;
    } else {
        horas = 24 - inicio + fim;
    }

    println!("O JOGO DUROU {} HORA(S)", horas);
}