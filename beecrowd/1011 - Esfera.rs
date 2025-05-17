use std::io;

fn volume_esfera(r: f64) -> f64 {
    const PI: f64 = 3.14159;

    let volume: f64 = (4.0 / 3.0) * PI * r * r * r;

    return volume;
}

fn main() {

    let mut line = String::new();

    io::stdin()
        .read_line(&mut line)
        .expect("Failed to read a line");

    let r: f64 = line.trim()
                    .parse::<f64>()
                    .expect("Failed to parse a floating point value");

    println!("VOLUME = {:.3}", volume_esfera(r));
}