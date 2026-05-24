#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::{Ordering, Reverse};
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

struct Scanner {
   buffer: VecDeque<String>,
   reader: io::BufReader<io::Stdin>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         reader: io::BufReader::new(io::stdin())
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();

         match self.reader.read_line(&mut input) {
            Ok(0) => {
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
            } Ok(_) => {
               
            } Err(e) => {
               return Err(e);
            }
         }
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();

         if self.buffer.is_empty() {
            self.buffer.push_back("".to_string());
         }
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct Rena {
    nome: String,
    peso: i32,
    idade: i32,
    altura: i32
}

fn cmp(a: &Rena, b: &Rena) -> Ordering {
    if a.peso != b.peso {
        return b.peso.cmp(&a.peso);
    } else if a.idade != b.idade {
        return a.idade.cmp(&b.idade);
    } else if a.altura != b.altura {
        return a.altura.cmp(&b.altura);
    }

    a.nome.cmp(&b.nome)
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let tc = sc.next::<usize>().unwrap();

    for i in 1..=tc {

        let n = sc.next::<usize>().unwrap();
        let m = sc.next::<usize>().unwrap();

        let mut renas = Vec::with_capacity(n);

        for _ in 0..n {
            let nome = sc.next::<String>().unwrap();
            let peso = sc.next::<i32>().unwrap();
            let idade = sc.next::<i32>().unwrap();
            let altura = (sc.next::<f64>().unwrap() * 100.0) as i32;

            renas.push(Rena {nome, peso, idade, altura});
        }

        renas.sort_by(|a, b| cmp(a, b));

        writeln!(writer, "CENARIO {{{}}}", i).ok();

        for i in 1..=m.min(n) {
            writeln!(writer, "{} - {}", i, renas[i - 1].nome).ok();
        }
    }
}