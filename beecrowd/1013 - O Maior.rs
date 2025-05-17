use std::io;

fn maior(a: i32, b: i32) -> i32 {
    return (a + b + (a - b).abs()) / 2;
}

fn read_line(a: &mut i32, b: &mut i32, c: &mut i32) {
    let mut linha = String::new();

    io::stdin()
        .read_line(&mut linha)
        .expect("Falha ao ler a linha");

    let valores: Vec<i32> = linha.split(" ")
                                .map(|x| x.trim().parse::<i32>().expect("Falha ao interpretar inteiro"))
                                .collect();

    *a = valores[0];
    *b = valores[1];
    *c = valores[2];
}

fn main() {

    let mut a: i32 = i32::default();
    let mut b: i32 = i32::default();
    let mut c: i32 = i32::default();
    
    read_line(&mut a, &mut b, &mut c);

    println!("{} eh o maior", maior(maior(a, b), c));
}