use std::io;

fn main() {

    const PI: f64 = 3.14159;

    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read a line");

    let r: f64 = input.trim()
                    .parse()
                    .expect("Failed to read a numeric value");

    let area: f64 = PI * r * r;

    println!("A={:.4}", area);
}