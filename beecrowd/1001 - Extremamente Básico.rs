use std::io;

fn main() {

    let mut first_input = String::new();
    let mut second_input = String::new();
    
    io::stdin()
        .read_line(&mut first_input)
        .expect("Failed to read line");

    io::stdin()
        .read_line(&mut second_input)
        .expect("Failed to read line");

    let a: i32 = first_input
                    .trim()
                    .parse()
                    .expect("Failed to parse in a integer");

    let b: i32 = second_input
                    .trim()
                    .parse()
                    .expect("Failed to parse in a integer");

    println!("X = {}", a + b);
}