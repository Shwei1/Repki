if __name__ == '__main__':
    n = int(input())
    matrix = list()
    for _ in range(n):
        matrix.append(list(map(int, input().split())))
    
    print(
        sum(
            [sum(row) for row in matrix if sum(row) == 1]
            )
        )
    
