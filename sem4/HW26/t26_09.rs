use std::io::{self, Read};
use std::collections::BinaryHeap;
use std::cmp::Reverse;

type Weight = i64;
type Node = usize;
type Edge = (Node, Weight);

fn handle_insecure(n: usize, adj: &[Vec<Edge>]) -> Option<Weight> {
    match n {
        0 | 1 => Some(0),
        2 => {
            for &(v, w) in &adj[0] {
                if v == 1 { return Some(w); }
            }
            None
        }
        _ => None,
    }
}

fn secure_cost(insecure: &[bool], adj: &[Vec<Edge>]) -> Option<Weight> {
    let n = insecure.len();

    let start = insecure.iter().position(|&b| !b)?;
    let mut visited = vec![false; n];
    let mut heap = BinaryHeap::new();
    let mut count = 0;
    let mut total = 0;

    visited[start] = true;
    count += 1;
    for &(v, w) in &adj[start] {
        if !insecure[v] {
            heap.push(Reverse((w, v)));
        }
    }

    while let Some(Reverse((w, u))) = heap.pop() {
        if visited[u] { continue; }
        visited[u] = true;
        count += 1;
        total += w;
        for &(v, w2) in &adj[u] {
            if !insecure[v] && !visited[v] {
                heap.push(Reverse((w2, v)));
            }
        }
    }

    let secure_count = insecure.iter().filter(|&&b| !b).count();
    if count == secure_count {
        Some(total)
    } else {
        None
    }
}

fn insecure_cost(insecure: &[bool], adj: &[Vec<Edge>]) -> Option<Weight> {
    let mut sum = 0;
    for i in 0..adj.len() {
        if insecure[i] {
            let mut best: Option<Weight> = None;
            for &(v, w) in &adj[i] {
                if !insecure[v] {
                    best = Some(best.map_or(w, |b| b.min(w)));
                }
            }
            sum += best?;
        }
    }
    Some(sum)
}

fn main() {

    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();
    let mut it = buf.split_whitespace();

    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let p = it.next().unwrap().parse::<usize>().unwrap();

    let mut insecure = vec![false; n];
    for _ in 0..p {
        let x = it.next().unwrap().parse::<usize>().unwrap();
        insecure[x - 1] = true;
    }

    let mut adj = vec![Vec::new(); n];
    for _ in 0..m {
        let u = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let v = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let w = it.next().unwrap().parse::<Weight>().unwrap();
        adj[u].push((v, w));
        adj[v].push((u, w));
    }

    let insecure_count = insecure.iter().filter(|&&b| b).count();

    if insecure_count == n {
        match handle_insecure(n, &adj) {
            Some(cost) => println!("{}", cost),
            None => println!("impossible"),
        }
        return;
    }

    let mst_cost = match secure_cost(&insecure, &adj) {
        Some(c) => c,
        None => { println!("impossible"); return; }
    };

    let attach_cost = match insecure_cost(&insecure, &adj) {
        Some(c) => c,
        None => { println!("impossible"); return; }
    };

    println!("{}", mst_cost + attach_cost);
}

