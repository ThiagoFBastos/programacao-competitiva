use std::io;

fn main() {

    let mut entrada: String = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma linha");

    let valores: Vec<f64> = entrada.trim()
                    .split(" ")
                    .map(|x| x.trim().parse::<f64>().expect("Falha ao interpretar como ponto flutuante"))
                    .collect();

    let n1 = valores[0];
    let n2 = valores[1];
    let n3 = valores[2];
    let n4 = valores[3];

    let media = (2.0 * n1 + 3.0 * n2 + 4.0 * n3 + n4) / 10.0;

    println!("Media: {:.1}", media);

    if media >= 7.0 {
        println!("Aluno aprovado.");
    } else if media >= 5.0 {
        println!("Aluno em exame.");

        entrada = String::new();

        io::stdin()
            .read_line(&mut entrada)
            .expect("Falha ao ler uma linha");

        let nota_exame = entrada.trim()
                            .parse::<f64>()
                            .expect("Falha ao interpretar como ponto flutuante");

        println!("Nota do exame: {:.1}", nota_exame);

        let media_final = (media + nota_exame) / 2.0;

        if media_final >= 5.0 {
            println!("Aluno aprovado.");
        } else {
            println!("Aluno reprovado.");
        }

        println!("Media final: {:.1}", media_final);

    } else {
        println!("Aluno reprovado.");
    }
}