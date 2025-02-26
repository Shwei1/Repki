use std::io;
use std::cmp::Ordering;

fn compare(a: u32, b: u32) -> Ordering {
    let ac = a % 10;
    let bc = b % 10;

    return ac.cmp(&bc)
            .then(a.cmp(&b));
}

fn selection_sort(vec: &mut Vec<u32>){
    for i in 0..vec.len(){
        let mut min_index: usize = i;

        for j in (i+1)..vec.len(){
            if compare(vec[j], vec[min_index]) == Ordering::Less {
                min_index = j;
            }
        }
        if min_index != i {
            vec.swap(i, min_index);
        }
    }

}

fn main(){
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().expect("Invalid number.");

    let mut numbers = Vec::<u32>::new();

    for i in 0..n {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let el: u32 = input.trim().parse().expect("Invalid number.");

        numbers.push(el);
    }

    selection_sort(&mut numbers);

    println!(
    "{}",
    numbers
        .iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ")
);

}
