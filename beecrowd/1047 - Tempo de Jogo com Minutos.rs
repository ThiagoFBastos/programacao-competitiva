use std::io;

fn read_4ints() -> (i32, i32, i32, i32) {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let valores: Vec<i32> = entrada.trim()
                                .split(" ")
                                .map(|x:&str| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                                .collect();

   return (valores[0], valores[1], valores[2], valores[3]);
}

fn to_minutes(h: i32, m: i32) -> i32 {
    return h * 60 + m;
}

fn diff_minutes(m1: i32, m2: i32) -> i32 {
    let mut diff = i32::default();

    if m1 < m2 {
        diff = m2 - m1;
    } else {
        diff = 24 * 60 - m1 + m2;
    }

    return diff;
}

fn show_hours(m: i32) {
    let h = m / 60;
    let m = m % 60;

    println!("O JOGO DUROU {} HORA(S) E {} MINUTO(S)", h, m);
}

fn main() {

    let (h1, m1, h2, m2) = read_4ints();

    let a = to_minutes(h1, m1);
    let b = to_minutes(h2, m2);

    show_hours(diff_minutes(a, b));
}