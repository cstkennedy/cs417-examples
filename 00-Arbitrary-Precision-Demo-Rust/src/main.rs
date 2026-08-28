use num_traits::Float;
use rand::distributions::{Distribution, Uniform};
use rand::prelude::*;

fn demonstrate_rounding(lower: f64, upper: f64) {
    let distribution = Uniform::new(lower, upper);
    let mut rng = rand::thread_rng();

    for _ in 0..10 {
        let random_t1: f64 = distribution.sample(&mut rng);
        let t1_as_t2: f32 = random_t1 as f32;

        println!("{random_t1}");
        println!("{t1_as_t2}");
        println!()
    }
}

fn demonstrate_underflow<const NUM_ITERATIONS: u64>() {
    let mut x: f64 = 4.62;

    for i in 0..NUM_ITERATIONS {
        x /= 1_000_000_000_000_000.0;
        println!("i: {i:3} - x: {x:.16e}");
    }
}

fn demonstrate_overflow<const NUM_ITERATIONS: u64>() {
    let mut x: f64 = 4.62;

    for i in 0..NUM_ITERATIONS {
        x *= 1_000_000_000.0;
        println!("i: {i:3} - x: {x:.16e}");
    }
}

fn print_heading(text: &str) {
    println!("{}", "-".repeat(60));
    println!("{:^60}", text);
    println!("{}", "-".repeat(60));
}

fn main() {
    print_heading("Demonstrate \"f64\" to \"f32\"");
    demonstrate_rounding(1_f64, 100_f64);

    print_heading("Demonstrate Underflow");
    demonstrate_underflow::<21>();

    println!();
    print_heading("Demonstrate Overflow");
    demonstrate_overflow::<33>();
}
