use std::io;
use std::cmp::Ordering;

#[derive(Clone)]
struct Pupil {
    surname: String,
    name: String,
    form: String,
    date: String,
}

fn parse_date(date: &str) -> (u32, u32, u32) {
    let mut parts = date.split('.');
    let day: u32 = parts.next().expect("Missing day").parse().expect("Invalid day");
    let month: u32 = parts.next().expect("Missing month").parse().expect("Invalid month");
    let year: u32 = parts.next().expect("Missing year").parse().expect("Invalid year");
    (day, month, year)
}

fn parse_form(form: &str) -> (u32, char) {
    let (num_str, letter_str) = form.split_at(form.len() - 1);
    let number: u32 = num_str.parse().expect("Invalid number");
    let letter = letter_str.chars().next().expect("Missing letter");
    (number, letter)
}

fn compare(p1: &Pupil, p2: &Pupil) -> Ordering {
    let f1 = parse_form(&p1.form);
    let f2 = parse_form(&p2.form);
    let d1 = parse_date(&p1.date);
    let d2 = parse_date(&p2.date);

    return f1.0.cmp(&f2.0).then(f1.1.cmp(&f2.1))
        .then(p1.surname.cmp(&p2.surname))
        .then(p1.name.cmp(&p2.name))
        .then(d1.2.cmp(&d2.2))
        .then(d1.1.cmp(&d2.1))
        .then(d1.0.cmp(&d2.0));
}

fn insertion_sort(vec: &mut Vec<Pupil>){
    for i in 0..vec.len(){
        let key = vec[i].clone();
        let mut j = i;
        while j != 0 && compare(&vec[j-1], &key) == Ordering::Greater {
            vec[j] = vec[j-1].clone();
            j -= 1;
        }
        vec[j] = key;
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: u32 = input.trim().parse().unwrap();

    let mut pupils: Vec<Pupil> = Vec::<Pupil>::new();

    for _ in 0..n{
        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read input.");
        let surname = input.trim().to_string();

        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read input.");
        let name = input.trim().to_string();

        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read input.");
        let form = input.trim().to_string();

        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read input.");
        let date = input.trim().to_string();

        let pupil = Pupil {surname, name, form, date};
        pupils.push(pupil);
    }

    insertion_sort(&mut pupils);

    for pupil in pupils {
        println!("{} {} {} {}", pupil.form, pupil.surname, pupil.name, pupil.date);
    }
}

