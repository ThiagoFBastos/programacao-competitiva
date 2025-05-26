fn main() {

    for i in (1..10).step_by(2) {
        println!("I={} J={}", i, 7);
        println!("I={} J={}", i, 6);
        println!("I={} J={}", i, 5);
    }
}