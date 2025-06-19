fn main() {

    let mut resposta = f64::default();

    for i in (1..40).step_by(2) {
        resposta += (i as f64) / 2.0_f64.powf((i / 2) as f64);
    }

    println!("{:.2}", resposta);
}