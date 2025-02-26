use std::io;

fn insertion_sort(vec: &mut Vec<u32>) {
    let len: usize = vec.len();
    for i in 1..len {
        let key = vec[i];
        let mut j = i;
        while j > 0 && vec[j-1] > key {
            vec[j] = vec[j-1];
            j -= 1;
        }
        vec[j] = key;
        if j != i {
            for (k, n) in vec.iter().enumerate() {
                if k > 0 {
                    print!(" ");
                }
                print!("{}", n);
            }
            println!();
        }
    }


}



fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();

    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");

    let mut values: Vec<u32> = input
        .trim()
        .split_whitespace()
        .take(n)
        .map(|s| s.parse().expect("Parse error"))
        .collect();

    insertion_sort(&mut values);
}

