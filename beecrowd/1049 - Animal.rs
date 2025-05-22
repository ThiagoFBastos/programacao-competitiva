use std::io;

fn read_line() -> String {
    let mut entrada = String::new();

    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler uma string");

    return entrada.trim().to_string();
}

fn main() {

    let classes = [
        (String::from("vertebrado"), String::from("ave"), String::from("carnivoro")),
        (String::from("vertebrado"), String::from("ave"), String::from("onivoro")),
        (String::from("vertebrado"), String::from("mamifero"), String::from("onivoro")),
        (String::from("vertebrado"), String::from("mamifero"), String::from("herbivoro")),
        (String::from("invertebrado"), String::from("inseto"), String::from("hematofago")),
        (String::from("invertebrado"), String::from("inseto"), String::from("herbivoro")),
        (String::from("invertebrado"), String::from("anelideo"), String::from("hematofago")),
        (String::from("invertebrado"), String::from("anelideo"), String::from("onivoro"))
    ];

    let animais = [
        "aguia",
        "pomba",
        "homem",
        "vaca",
        "pulga",
        "lagarta",
        "sanguessuga",
        "minhoca"
    ];

    let a = read_line();
    let b = read_line();
    let c = read_line();

    let tripla = (a, b, c);

    for (i, classe) in classes.iter().enumerate() {

        if tripla == *classe {
            println!("{}", animais[i]);
            break;
        }
    }
}