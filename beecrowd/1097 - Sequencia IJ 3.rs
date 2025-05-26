fn main() {

    for i in (1..10).step_by(2) {
        println!("I={} J={}", i, 6 + i);
        println!("I={} J={}", i, 5 + i);
        println!("I={} J={}", i, 4 + i);
    }
}