use std::io;

fn triangulo(b: f64, h: f64) -> f64 {
    return b * h / 2.0;
}

fn circulo(r: f64) -> f64 {
    const PI: f64 = 3.14159;
    return r * r * PI;
}

fn trapezio(a: f64, b: f64, h: f64) -> f64 {
    return (a + b) * h / 2.0;
}

fn quadrado(l: f64) -> f64 {
    return l * l;
}

fn retangulo(a: f64, b: f64) -> f64 {
    return a * b;
}

fn read_line(a: &mut f64, b: &mut f64, c: &mut f64) {
    let mut linha = String::new();

    io::stdin()
        .read_line(&mut linha)
        .expect("Falha ao ler a linha");

    let valores: Vec<f64> = linha.split(" ")
                                .map(|x| x.trim().parse::<f64>().expect("Falha ao interpretar ponto flutuante"))
                                .collect();

    *a = valores[0];
    *b = valores[1];
    *c = valores[2];
}

fn main() {

    let mut a: f64 = f64::default();
    let mut b: f64 = f64::default();
    let mut c: f64 = f64::default();
    
    read_line(&mut a, &mut b, &mut c);

    println!("TRIANGULO: {:.3}", triangulo(a, c));
    println!("CIRCULO: {:.3}", circulo(c));
    println!("TRAPEZIO: {:.3}", trapezio(a, b, c));
    println!("QUADRADO: {:.3}", quadrado(b));
    println!("RETANGULO: {:.3}", retangulo(a, b));
}