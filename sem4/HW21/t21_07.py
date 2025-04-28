if __name__ == '__main__':
    n, m = map(int, input().split())
    degrees = [[i, 0] for i in range(1, n+2)]
    for _ in range(m):
        u, v = map(int, input().split())
        degrees[u][1] += 1
        degrees[v][1] += 1
    
    for [v, deg] in degrees[1:]:
        print(deg)
    
    
