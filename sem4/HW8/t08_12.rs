use std::io;

fn selection_sort(vec: &mut Vec<u32>) -> u32 {
    let mut count: u32 = 0;
    let mut first_element_index: usize = 0;
    
    for i in 0..vec.len(){
        let mut min_index: usize = i;

        for j in (i+1)..vec.len(){
            if vec[j] < vec[min_index] {
                min_index = j;
            }
        }

        if min_index != i {
            if first_element_index == i {
                first_element_index = min_index;
                count += 1;
            } else if first_element_index == min_index {
                first_element_index = i;
                count += 1;
            }
            vec.swap(min_index, i);
        }
    }
    count
}


fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();

    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let mut numbers: Vec<u32> = input
                                .trim()
                                .split_whitespace()
                                .map(|s| s.parse().unwrap())
                                .collect();

    let answer = selection_sort(&mut numbers);
    println!("{}", answer);
}

