use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao ler inteiro");
}

fn main() {

    let mut alcool = i32::default();
    let mut gasolina = i32::default();
    let mut diesel = i32::default();

    loop {

        let combustivel = read_int();

        match combustivel {
            1 => alcool += 1,
            2 => gasolina += 1,
            3 => diesel += 1,
            4 => break,
            _ => continue
        }
    }

    println!("MUITO OBRIGADO");
    println!("Alcool: {}", alcool);
    println!("Gasolina: {}", gasolina);
    println!("Diesel: {}", diesel);
}