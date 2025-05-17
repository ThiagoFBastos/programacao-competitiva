use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let dinheiro: f64 = entrada.trim()
                            .parse::<f64>()
                            .expect("Falha ao interpretar como ponto flutuante");

    let notas = [100.0, 50.0, 20.0, 10.0, 5.0, 2.0]; 
    let moedas = [1.0, 0.5, 0.25, 0.10, 0.05, 0.01];

    let mut dinheiro_total = (dinheiro * 100.0) as i32;

    println!("NOTAS:");

    for valor in &notas {
        let valor_multiplicado = (valor * 100.0) as i32;
        let quantidade = dinheiro_total / valor_multiplicado;
        dinheiro_total %= valor_multiplicado;
        println!("{} nota(s) de R$ {:.2}", quantidade, valor);
    }

    println!("MOEDAS:");

    for valor in &moedas {
        let valor_multiplicado = (valor * 100.0) as i32;
        let quantidade = dinheiro_total / valor_multiplicado;
        dinheiro_total %= valor_multiplicado;
        println!("{} moeda(s) de R$ {:.2}", quantidade, valor);
    }
}