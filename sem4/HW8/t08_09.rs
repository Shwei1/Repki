use std::cmp::Ordering;

fn weight(mut n: u64) -> u64 {
    let mut sum: u64 = 0;
    while n > 0 {
        sum += n % 10;
        n /= 10;
    }
    sum
}

fn compare(a: u64, b: u64) -> Ordering {
    let wa = weight(a);
    let wb = weight(b);
    if wa < wb {
        Ordering::Less
    } else if wa > wb {
        Ordering::Greater
    } else {
        a.to_string().cmp(&b.to_string())
    }
}

fn binary_search(vec: &mut Vec<u64>, key: u64) -> usize {
    let mut left = 0;
    let mut right = vec.len();

    while left < right {
        //let middle = left + (right - left) / 2;
        let middle = (left + right) / 2;
        if compare(vec[middle], key) == Ordering::Less {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }
    right
}

fn insertion_sort(vec: &mut Vec<u64>) {
    for i in 1..vec.len() {
        let key = vec[i];
        let mut j = i;
        while j > 0 && compare(vec[j - 1], key) == Ordering::Greater {
            vec[j] = vec[j - 1];
            j -= 1;
        }
        vec[j] = key;
    }
}

fn main() {

    let mut input1 = String::new();
    let mut input2 = String::new();

    std::io::stdin().read_line(&mut input1)
        .expect("Failed to handle input.");
    let n: u64 = input1.trim().parse()
        .expect("Failed to parse n.");

    std::io::stdin().read_line(&mut input2)
        .expect("Failed to handle input.");
 
    let k: u64 = input2.trim().parse()
        .expect("Failed to parse k.");

    let mut numbers: Vec<u64> = (1..=n).collect();

    insertion_sort(&mut numbers);

    let rank = binary_search(&mut numbers, k);

    let kth_element = numbers[(k - 1) as usize];

    println!("{}", rank+1);
    println!("{}", kth_element);
}

