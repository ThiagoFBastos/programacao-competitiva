fn main() {

    for i in 0..=10 {
        println!("I={} J={}", (i as f64) * 2.0 / 10.0, 1.0 + (i as f64) * 2.0 / 10.0);
        println!("I={} J={}", (i as f64) * 2.0 / 10.0, 2.0 + (i as f64) * 2.0 / 10.0);
        println!("I={} J={}", (i as f64) * 2.0 / 10.0, 3.0 + (i as f64) * 2.0 / 10.0);
    }
}