use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao interpretar como inteiro");
}

fn main() {

    let n = read_int();

    let mut dentro = i32::default();
    let mut fora = i32::default();

    for _i in 1..=n {
        let numero = read_int();

        if numero >= 10 && numero <= 20 {
            dentro += 1;
        } else {
            fora += 1;
        }
    }

    println!("{} in", dentro);
    println!("{} out", fora);
}