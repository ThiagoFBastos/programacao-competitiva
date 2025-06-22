use std::io::stdin;

fn read_vector() -> Vec<i32> {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler a linha");

    let numbers: Vec<i32> = input.trim()
                                .split(" ")
                                .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                                .collect();

    return numbers;
}

fn has_triangle(numbers: &mut Vec<i32>) -> bool {
    numbers.sort();
    numbers.reverse();

    for i in 0..=3 {
        for j in i+1..=3 {
            for k in j+1..=3 {
                if numbers[i] < numbers[j] + numbers[k] {
                    return true;
                }
            }
        }
    }

    return false;
}

fn main() {

     let mut numbers: Vec<i32> = read_vector();

     if has_triangle(&mut numbers) {
        println!("S");
     } else {
        println!("N");
     }
}