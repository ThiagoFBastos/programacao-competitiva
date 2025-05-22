use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao interpretar como inteiro");
}

fn main() {

    let mut pares = i32::default();
    let mut impares = i32::default();
    let mut positivos = i32::default();
    let mut negativos = i32::default();

    for _i in 1..=5 {
        let numero: i32 = read_int();

        if numero % 2 == 0 {
            pares += 1;
        } else {
            impares += 1;
        }

        if numero > 0 {
            positivos += 1;
        } else if numero < 0 {
            negativos += 1;
        }
    }

    println!("{} valor(es) par(es)", pares);
    println!("{} valor(es) impar(es)", impares);
    println!("{} valor(es) positivo(s)", positivos);
    println!("{} valor(es) negativo(s)", negativos);
}