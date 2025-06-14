fn main() {

    let mut resposta = f64::default();

    for i in 1..=100 {
        resposta += 1.0 / (i as f64);
    }

    println!("{:.2}", resposta);
}