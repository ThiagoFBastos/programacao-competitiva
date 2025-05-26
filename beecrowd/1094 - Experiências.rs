use std::io;

fn read_int() -> i32 {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().parse::<i32>().expect("Falha ao ler inteiro");
}

fn read_line() -> (i32, char) {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    let valores: Vec<&str> = entrada.trim()
                                .split(" ")
                                .collect();

    let a = valores[0].trim().parse::<i32>().expect("Falha ao ler inteiro");
    let b = valores[1].trim().parse::<char>().expect("Falha ao ler char");

    return (a, b);
}

fn main() {

    let casos = read_int();
    
    let mut coelhos = i32::default();
    let mut ratos = i32::default();
    let mut sapos = i32::default();

    for _i in 1..=casos {
        let (quantidade, tipo) = read_line();

        match tipo {
            'C' => coelhos += quantidade,
            'R' => ratos += quantidade,
            'S' => sapos += quantidade,
            _ => panic!("Valor incorreto")
        };
    }

    let total = coelhos + ratos + sapos;

    println!("Total: {} cobaias", total);
    println!("Total de coelhos: {}", coelhos);
    println!("Total de ratos: {}", ratos);
    println!("Total de sapos: {}", sapos);
    println!("Percentual de coelhos: {:.2} %", (coelhos as f64) / (total as f64) * 100.0);
    println!("Percentual de ratos: {:.2} %", (ratos as f64) / (total as f64) * 100.0);
    println!("Percentual de sapos: {:.2} %", (sapos as f64) / (total as f64) * 100.0);
}