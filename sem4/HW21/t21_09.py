if __name__ == '__main__':
    n, m = map(int, input().split())

    edges = set()

    for _ in range(m):
        edges.add(tuple(map(int, input().split())))

    print("YES" if len(edges) == n * (n-1) / 2 else "NO")

