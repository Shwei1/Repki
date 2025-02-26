use std::io;
use std::cmp::Ordering;

fn compare_strings(s1: &str, s2: &str) -> Ordering {

    let bytes1 = s1.as_bytes();
    let bytes2 = s2.as_bytes();
    let len = if bytes1.len() > bytes2.len() {bytes2.len()} else {bytes1.len()};

    for i in 0..len{
        if bytes1[i] > bytes2[i] {
            return Ordering::Greater;
        }
        else if bytes1[i] < bytes2[i] {
            return Ordering::Less;
        }
    }
    bytes1.len().cmp(&bytes2.len())
}

fn selection_sort(vec: &mut Vec<String>) {
    let len = vec.len();
    for i in 0..len {
        let mut min_index = i;
        for j in (i + 1)..len {
            if compare_strings(&vec[j], &vec[min_index]) == Ordering::Less {
                min_index = j;
            }
        }
        if min_index != i {
            vec.swap(i, min_index);
        }
    }
}

fn main() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).expect("Failed to read line");
    let n: usize = input.trim().parse().expect("Please enter a valid number");

    let mut orc_words = Vec::<String>::new();

    for _i in 0..n {
        let mut buffer = String::new();
        io::stdin().read_line(&mut buffer).expect("Failed to read line");
        orc_words.push(buffer.trim_end().to_string());
    }

    selection_sort(&mut orc_words);

    for word in &orc_words {
    println!("{}", word);
    }
}

