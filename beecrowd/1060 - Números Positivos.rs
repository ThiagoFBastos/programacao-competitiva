use std::io;

fn main() {

   let mut positivos = i32::default();

   for _i in 1..=6 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler a entrada");

    let numero = entrada.trim()
                    .parse::<f64>()
                    .expect("Falha ao ler ponto flutuante");

    if numero > 0.0 {
        positivos += 1;
    }
   }

   println!("{} valores positivos", positivos);
}