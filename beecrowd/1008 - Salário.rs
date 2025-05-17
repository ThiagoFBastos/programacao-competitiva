use std::io;

fn main() {

    let mut first_line = String::new();
    let mut second_line = String::new();
    let mut third_line = String::new();

    io::stdin()
        .read_line(&mut first_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut second_line)
        .expect("Failed to read a line");

    io::stdin()
        .read_line(&mut third_line)
        .expect("Failed to read a line");

    let id: i32 = first_line.trim()
                    .parse::<i32>()
                    .expect("Failed to parse a integer value");

    let work_hours: i32 = second_line.trim()
                            .parse::<i32>()
                            .expect("Failed to parse a integer value");

    let hour_salary: f64 = third_line.trim()
                        .parse::<f64>()
                        .expect("Failed to parse a floating point value");

    let salary: f64 = hour_salary * (work_hours as f64);

    println!("NUMBER = {}", id);
    println!("SALARY = U$ {:.2}", salary);
}