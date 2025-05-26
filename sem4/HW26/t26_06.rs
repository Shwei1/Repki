use std::io;

struct Edge { u: usize, v: usize, w: f64 }

fn Prim(s: usize, coords: &[(i32, i32)]) -> f64 {
    let p = coords.len();

    let mut dist = vec![vec![0.0; p]; p];
    for i in 0..p {
        for j in (i + 1)..p {
            let dx = (coords[i].0 - coords[j].0) as f64;
            let dy = (coords[i].1 - coords[j].1) as f64;
            let d = (dx * dx + dy * dy).sqrt();
            dist[i][j] = d;
            dist[j][i] = d;
        }
    }

    let mut used = vec![false; p];
    let mut min_edge = vec![f64::INFINITY; p];
    let mut parent = vec![None; p];
    let mut mst_edges = Vec::with_capacity(p - 1);

    min_edge[0] = 0.0;
    for _ in 0..p {
        let v = (0..p)
            .filter(|&i| !used[i])
            .min_by(|&i, &j| min_edge[i].partial_cmp(&min_edge[j]).unwrap())
            .unwrap();

        used[v] = true;
        if parent[v].is_some() {
            mst_edges.push(min_edge[v]);
        }

        for to in 0..p {
            if !used[to] && dist[v][to] < min_edge[to] {
                min_edge[to] = dist[v][to];
                parent[to] = Some(v);
            }
        }
    }

    mst_edges.sort_by(|a, b| b.partial_cmp(a).unwrap());
    mst_edges[s - 1]
}

fn main() -> io::Result<()> {
    let mut input = String::new();

    io::stdin().read_line(&mut input)?;
    let n: usize = input.trim().parse().unwrap();

    for _case in 0..n {
        input.clear();
        io::stdin().read_line(&mut input)?;
        let mut iter = input.split_whitespace();
        let s: usize = iter.next().unwrap().parse().unwrap();
        let p: usize = iter.next().unwrap().parse().unwrap();

        let mut coords = Vec::with_capacity(p);
        for _ in 0..p {
            input.clear();
            io::stdin().read_line(&mut input)?;
            let mut it = input.split_whitespace();
            let x: i32 = it.next().unwrap().parse().unwrap();
            let y: i32 = it.next().unwrap().parse().unwrap();
            coords.push((x, y));
        }

        let answer = Prim(s, &coords);
        println!("{:.2}", answer);
    }

    Ok(())
}

