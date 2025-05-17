use std::io;

fn main() {

    let mut first_line = String::new();
    let mut second_line = String::new();
    let mut third_line = String::new();
    let mut fourth_line = String::new();

    io::stdin()
        .read_line(&mut first_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut second_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut third_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut fourth_line)
        .expect("Failed to read a line");

    let a: i32 = first_line.trim()
                    .parse()
                    .expect("Failed to parse a integer value");

    let b: i32 = second_line.trim()
                    .parse()
                    .expect("Failed to parse a integer value");

    let c: i32 = third_line.trim()
                    .parse()
                    .expect("Failed to parse a integer value");

    let d: i32 = fourth_line.trim()
                    .parse()
                    .expect("Failed to parse a integer value");

    let diff: i32 = a * b - c * d;

    println!("DIFERENCA = {}", diff);
}