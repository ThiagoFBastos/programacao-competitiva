fn main() {

    let mut i = 1;
    let mut j = 60;
    
    loop {
        println!("I={} J={}", i, j);
        i += 3;
        j -= 5;
        if j < 0 {
            break;
        }
    }
}