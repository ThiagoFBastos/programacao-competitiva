use std::io::stdin;

fn read_int() -> i32 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn read_float() -> f64 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim()
            .parse::<f64>()
            .expect("Falha ao interpretar como ponto flutuante");
}

fn read_char() -> char {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim()
            .parse::<char>()
            .expect("Falha ao interpretar como caracter");
}

fn sum(matrix: Vec<Vec<f64>>, line: i32) -> f64 {
    let mut ans = f64::default();

    for j in 0..=11 {
        ans += matrix[line as usize][j as usize];
    }

    return ans;
}

fn average(matrix: Vec<Vec<f64>>, line: i32) -> f64 {
    let mut ans = f64::default();

    for j in 0..=11 {
        ans += matrix[line as usize][j as usize];
    }

    return ans / 12.0;
}

fn main() {

    let line = read_int();

    let operation = read_char();

    let mut matrix = vec![vec![0.0; 12]; 12];

    for i in 0..=11 {
        for j in 0..=11 {
            matrix[i][j] = read_float();
        }
    }

    if operation == 'S' {
        println!("{:.1}", sum(matrix, line));
    } else {
        println!("{:.1}", average(matrix, line));
    }
}