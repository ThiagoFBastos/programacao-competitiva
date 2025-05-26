use std::io::stdin;

fn swap(a: &mut i32, b: &mut i32) {
    let tmp = *a;
    *a = *b;
    *b = tmp;
}

fn sum(a: i32, b: i32) -> i32 {
    let mut x = a;
    let mut y = b;

    if x > y {
        swap(&mut x, &mut y);
    }

    x += 1;
    y -= 1;

    if x % 2 == 0 {
        x += 1;
    }

    if y % 2 == 0 {
        y -= 1;
    }

    if x > y {
        return 0;
    }

    let n = (y - x + 2) / 2;

    return n * (x + y) / 2;
}

fn read_int() -> i32 {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    return input.trim()
            .parse::<i32>()
            .expect("Falha ao interpretar como inteiro");
}

fn read_line() -> (i32, i32) {
    let mut input = String::new();

    stdin()
        .read_line(&mut input)
        .expect("Falha ao ler uma string");

    let values: Vec<i32> = input.trim()
                            .split_whitespace()
                            .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar como inteiro"))
                            .collect();

    return match values.as_slice() {
        [a, b] => (*a, *b),
        _ => panic!("Número incorreto de parâmetros")
    };
}

fn main() {

    let cases = read_int();

    for _i in 1..=cases {
        let (x, y) = read_line();

        println!("{}", sum(x, y));
   }
}