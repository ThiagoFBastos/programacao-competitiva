use std::io;

fn main() {

    let mut first_line = String::new();
    let mut second_line = String::new();

    io::stdin()
        .read_line(&mut first_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut second_line)
        .expect("Failed to read a line");

    let a: f64 = first_line.trim()
                    .parse()
                    .expect("Failed to parse a floating point value");

    let b: f64 = second_line.trim()
                    .parse()
                    .expect("Failed to parse a floating point value");

    let media: f64 = (a * 3.5 + b * 7.5) / 11.0;

    println!("MEDIA = {:.5}", media);
}