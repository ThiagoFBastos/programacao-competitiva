use std::io;

fn read_line(a: &mut f64, b: &mut f64) {
    let mut linha: String = String::new();

    io::stdin()
        .read_line(&mut linha)
        .expect("Falha ao tentar ler a linha");

    let valores: Vec<f64> = linha.split(" ")
                            .map(|x: &str| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                            .collect();

    *a = valores[0];
    *b = valores[1];
}

fn main() {

   let (mut x1, mut y1) = (f64::default(), f64::default());
   let (mut x2, mut y2) = (f64::default(), f64::default());

   read_line(&mut x1, &mut y1);
   read_line(&mut x2, &mut y2);

   let dist = ((x1 - x2).powf(2.0) + (y1 - y2).powf(2.0)).sqrt();

   println!("{:.4}", dist);
}