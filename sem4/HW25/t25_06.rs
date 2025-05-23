use std::io;
use std::collections::HashMap;

fn bellman_ford(table: &HashMap<(i32, i32), i32>, graph: &Vec<Vec<i32>>) -> i32{
    let n = graph.len();
    let INF = 1000000;
    let mut dist: Vec<i32> = vec![INF; n];
    let start = 0;
    let end = n - 1;
    dist[start] = 0;

    for i in 0..(n-1) {
        for u in 0..n {
            for &v in &graph[u] {
                let w = *table.get(&(u as i32, v)).unwrap_or(&INF);
                if dist[u] != INF && dist[u] + w < dist[v as usize] {
                    dist[v as usize] = dist[u] + w;
                }
            }
        }
    }

    if dist[end] != INF {return dist[end];}
    else {return -1;}
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();

    let mut graph: Vec<Vec<i32>> = vec![Vec::new(); n];
    let mut route_prices: HashMap<(i32, i32), i32> = HashMap::new();

    input.clear();
    io::stdin().read_line(&mut input).unwrap();

    let gas_prices: Vec<i32> = input
        .split_whitespace()
        .map(|s| s.parse::<i32>().unwrap())
        .collect();

    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let m: usize = input.trim().parse().unwrap();

    let mut numbers: Vec<i32> = Vec::new();

    while numbers.len() < 2 * m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        numbers.extend(
            input
            .split_whitespace()
            .map(|s| s.parse::<i32>().unwrap())
        );
    }

    for pair in numbers.chunks(2).take(m) {
        let a = pair[0];
        let b = pair[1];

        graph[a as usize - 1].push(b - 1);
        graph[b as usize-1].push(a-1);
        route_prices.insert((a - 1, b - 1), gas_prices[a as usize - 1]);
        route_prices.insert((b - 1, a - 1), gas_prices[b as usize - 1]);
    }

    // for (i, nbrs) in graph.iter().enumerate() {
    //     eprintln!("city {}: {:?}", i+1, nbrs);
    // }

    // eprintln!("pairs = {:?}", numbers);

    println!("{}", bellman_ford(&route_prices, &graph));
}

