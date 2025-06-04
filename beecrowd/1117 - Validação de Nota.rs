use std::io;

fn read_float() -> f64 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim()
                .parse::<f64>()
                .expect("Falha ao ler ponto flutuante");
}

fn main() {

    let mut notas_validas = i32::default();
    let mut soma_notas = f64::default();

    while notas_validas != 2 {
        let nota = read_float();
        
        if nota >= 0.0 && nota <= 10.0 {
            notas_validas += 1;
            soma_notas += nota;
        } else {
            println!("nota invalida");
        }
    }

    println!("media = {:.2}", soma_notas / 2.0);
}