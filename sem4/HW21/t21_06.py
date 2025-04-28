if __name__ == '__main__':
    n, m = map(int, input().split())
    degrees = [[0, 0] for _ in range(1, n+2)]
    for _ in range(m):
        u, v = map(int, input().split())
        degrees[v][0] += 1
        degrees[u][1] += 1
    
    for [into, outof] in degrees[1:]:
        print(into, outof)

