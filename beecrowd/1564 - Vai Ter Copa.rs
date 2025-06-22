use std::io::{self, BufRead};

fn main() {

    for line in io::stdin().lock().lines() {
        match line {
            Ok(text) => {
                let n = text.trim()
                            .parse::<i32>()
                            .expect("Falha ao interpretar como inteiro");

                if n == 0 {
                    println!("vai ter copa!");
                } else {
                    println!("vai ter duas!");
                }
            },
            Err(_err) => break
        }
    }
}