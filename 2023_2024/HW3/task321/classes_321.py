


class Equation():
    INF = "Infinity"
    def __init__(self, b, c):
        self.b = b
        self.c = c

    def __str__(self):
        return f'{self.b}x + {self.c} = 0'

    def solve(self):
        if self.b == 0:
            if self.c == 0:
                return Equation.INF
            else:
                return ()
        else:
            return (-self.c / self.b,)


class QuadraticEquation(Equation):
    def __init__(self, a, b, c):
        super().__init__(b, c)
        self.a = a

    def discriminant(self):
        return (self.b ** 2 - 4 * self.a * self.c)

    def __str__(self):
        return f"{self.a}x^2 + {self.b}x + {self.c} = 0"

    def solve(self):
        if self.a == 0:
            return super().solve()
        else:
            d = self.discriminant()
            if d < 0:
                return ()
            if d == 0:
                x1 = -self.b / (2 * self.a)
                return (x1,)
            if d > 0:
                x1 = (-self.b + d ** 0.5) / (2 * self.a)
                x2 = (-self.b - d ** 0.5) / (2 * self.a)
                return (x1, x2)


class BiQuadraticEquation(QuadraticEquation):
    def __init__(self, a, b, c):
        super().__init__(a, b, c)

    def __str__(self):
        return f"{self.a}x^4 + {self.b}x^2 + {self.c} = 0"

    def solve(self):
        solutions = set()
        quadratic_solutions = super().solve()
        if quadratic_solutions == BiQuadraticEquation.INF:
            return BiQuadraticEquation.INF
        for solution in quadratic_solutions:
            if solution >= 0:
                q_1 = solution ** 0.5
                q_2 = -1 * q_1
                solutions.add(q_1)
                solutions.add(q_2)
        return tuple(solutions)


#
# if __name__ == "__main__":
#     print(QuadraticEquation(0, 0, 4).solve())
