if __name__ == '__main__':
    n, m = map(int, input().split())
    edges = set()
    ok = True
    for _ in range(m):
        (u, v) = tuple(map(int, input().split()))
        if (u, v) in edges:
            ok = False
            print("YES")
            break
        else:
            edges.add((u, v))
    

    if ok: print("NO")

