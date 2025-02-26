use std::io;
use std::cmp::Ordering;

#[derive(Copy, Clone)]
struct Time {
    hours: u32,
    minutes: u32,
    seconds: u32,
}

fn compare(t1: &Time, t2: &Time) -> Ordering {
    t1.hours.cmp(&t2.hours)
        .then(t1.minutes.cmp(&t2.minutes))
        .then(t1.seconds.cmp(&t2.seconds))
}

fn insertion_sort(vec: &mut Vec<Time>){
    for i in 0..vec.len(){
        let key = vec[i];
        let mut j = i;
        while j > 0 && compare(&vec[j-1], &key) == Ordering::Greater {
            vec[j] = vec[j-1];
            j -= 1;
        }
        vec[j] = key;
    }

}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();

    let mut times: Vec<Time> = Vec::<Time>::new();
    for _ in 0..n{
        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let mut iter = input.trim().split_whitespace();
    
        let hh: u32 = iter.next().unwrap().parse().expect("Failed to parse x");
        let mm: u32 = iter.next().unwrap().parse().expect("Failed to parse y");
        let ss: u32 = iter.next().unwrap().parse().expect("Failed to parse z");

        let time = Time {
            hours: hh,
            minutes: mm,
            seconds: ss,
        };

        times.push(time);
    }

    insertion_sort(&mut times);

    for time in times {
        println!("{} {} {}", time.hours, time.minutes, time.seconds);
    }
}
