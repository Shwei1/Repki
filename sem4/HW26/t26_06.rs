use std::io;

fn euclid(x: i32, y: i32) -> i32 {
    return



}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: i32 = input.trim().parse().unwrap();

    println!("{} {}", n / 10, n % 10);
}

