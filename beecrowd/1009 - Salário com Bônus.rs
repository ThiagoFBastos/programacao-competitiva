use std::io;

fn main() {

    let mut name = String::new();
    let mut second_line = String::new();
    let mut third_line = String::new();

    io::stdin()
        .read_line(&mut name)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut second_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut third_line)
        .expect("Failed to read a line");

   let salary: f64 = second_line.trim()
                        .parse::<f64>()
                        .expect("Failed to parse a floating point");

    let sales: f64 = third_line.trim()
                        .parse::<f64>()
                        .expect("Failed to parse a floating point");

    let total_salary: f64 = salary + sales * 0.15;

    println!("TOTAL = R$ {:.2}", total_salary);
}