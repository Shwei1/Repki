use std::io;

fn bubble_sort(vec: &mut Vec<i32>) -> u64{
    let len: usize = vec.len();
    let mut swapcount: u64 = 0;
    for _i in 0..len{
        let mut swapped: bool = false;
        for j in 0..len - 1{
            if vec[j] > vec[j+1]{
                swapped = true;
                vec.swap(j, j+1);
                swapcount += 1;
            }
        }
        if !swapped {
            break;
        }
    }
    swapcount
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let n: usize = input.trim().parse().expect("Please enter a valid number");

    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");

    let mut values: Vec<i32> = input
        .trim()
        .split_whitespace()
        .take(n)
        .map(|s| s.parse().expect("Parse error"))
        .collect();

    let answer: u64 = bubble_sort(&mut values);
    println!("{}", answer);
}

