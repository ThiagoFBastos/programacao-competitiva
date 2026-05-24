#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{HashMap, VecDeque};
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

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let mut christmas = HashMap::new();

    christmas.insert("brasil".to_string(), "Feliz Natal!".to_string());
    christmas.insert("alemanha".to_string(), "Frohliche Weihnachten!".to_string());
    christmas.insert("austria".to_string(), "Frohe Weihnacht!".to_string());
    christmas.insert("coreia".to_string(), "Chuk Sung Tan!".to_string());
    christmas.insert("espanha".to_string(), "Feliz Navidad!".to_string());
    christmas.insert("grecia".to_string(), "Kala Christougena!".to_string());
    christmas.insert("estados-unidos".to_string(), "Merry Christmas!".to_string());
    christmas.insert("inglaterra".to_string(), "Merry Christmas!".to_string());
    christmas.insert("australia".to_string(), "Merry Christmas!".to_string());
    christmas.insert("portugal".to_string(), "Feliz Natal!".to_string());
    christmas.insert("suecia".to_string(), "God Jul!".to_string());
    christmas.insert("turquia".to_string(), "Mutlu Noeller".to_string());
    christmas.insert("argentina".to_string(), "Feliz Navidad!".to_string());
    christmas.insert("chile".to_string(), "Feliz Navidad!".to_string());
    christmas.insert("mexico".to_string(), "Feliz Navidad!".to_string());
    christmas.insert("antardida".to_string(), "Merry Christmas!".to_string());
    christmas.insert("canada".to_string(), "Merry Christmas!".to_string());
    christmas.insert("irlanda".to_string(), "Nollaig Shona Dhuit!".to_string());
    christmas.insert("belgica".to_string(), "Zalig Kerstfeest!".to_string());
    christmas.insert("italia".to_string(), "Buon Natale!".to_string());
    christmas.insert("libia".to_string(), "Buon Natale!".to_string());
    christmas.insert("siria".to_string(), "Milad Mubarak!".to_string());
    christmas.insert("marrocos".to_string(), "Milad Mubarak!".to_string());
    christmas.insert("japao".to_string(), "Merii Kurisumasu!".to_string());

    loop {
        let country = sc.next::<String>();

        if country.is_err() {
            break;
        }

        let name = country.unwrap();

        if let Some(merry_christmas) = christmas.get(&name) {
            writeln!(writer, "{}", merry_christmas).ok();
        } else {
            writeln!(writer, "--- NOT FOUND ---").ok();
        }
    }
}