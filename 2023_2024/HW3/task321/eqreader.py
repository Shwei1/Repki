from HW3.task321.classes_321 import *


class Output():
    def __init__(self, filename):
        self.filename = filename

    def reader(self):
        equations = []
        with open(self.filename, "rt") as f:
            for line in f:
                eq = [float(n) for n in line.split()]
                equations.append(eq)
        return equations

    def apparent_equations(self):
        str_eqs = []
        for args in self.reader():
            if len(args) == 2:
                str_eqs.append(f"{args[0]}x + {args[1]} = 0")
            elif len(args) == 3:
                str_eqs.append(f"{args[0]}x^2 + {args[1]}x + {args[2]} = 0")
            elif len(args) == 5:
                str_eqs.append(f"{args[0]}x^4 + {args[2]}x^2 + {args[4]} = 0")
        return str_eqs

    def initiate(self):
        arguments = self.reader()
        equations = []
        for arg in arguments:
            if len(arg) == 2:
                e = Equation(arg[0], arg[1])
                equations.append(e)
            elif len(arg) == 3:
                e = QuadraticEquation(arg[0], arg[1], arg[2])
                equations.append(e)
            elif len(arg) == 5:
                e = BiQuadraticEquation(arg[0], arg[2], arg[4])
                equations.append(e)
        return equations

    def solver(self):
        equations = self.initiate()
        solutions = []
        for eq in equations:
            solutions.append(eq.solve())
        return solutions

    def show(self):
        solutions = self.solver()
        equations = self.apparent_equations()
        for eq in equations:
            print(f"Solutions for equation {eq} from file {self.filename} are such: {solutions[equations.index(eq)]}")

    def solution_counter(self, required_num):
        eqs_req_sol = []
        eqs = self.initiate()
        for eq in eqs:
            if type(required_num) == int:
                if len(eq.solve()) == required_num:
                    eqs_req_sol.append(str(eq))
            elif type(required_num) == str:
                if eq.solve() == Equation.INF:
                    eqs_req_sol.append(str(eq))
        return eqs_req_sol

    def solution_counter_classtype(self, required_num):  # Те саме, що й зверху, але повертає об'єкт класу рівняння, а не строки
        eqs_req_sol = []
        eqs = self.initiate()
        for eq in eqs:
            if type(required_num) == int:
                if len(eq.solve()) == required_num:
                    eqs_req_sol.append(eq)
            elif type(required_num) == str:
                if eq.solve() == Equation.INF:
                    eqs_req_sol.append(eq)
        return eqs_req_sol

    def max_finder(self):
        equations = self.solution_counter_classtype(1)
        maxsol = equations[0].solve()[0]
        eqnum = 0
        for i in range(len(equations)):
            if equations[i].solve()[0] > maxsol:
                maxsol = equations[i].solve()[0]
                eqnum = i
        return equations[eqnum]

    def min_finder(self):
        equations = self.solution_counter_classtype(1)
        minsol = equations[0].solve()[0]
        eqnum = 0
        for i in range(len(equations)):
            if equations[i].solve()[0] < minsol:
                minsol = equations[i].solve()[0]
                eqnum = i
        return equations[eqnum]





    def output(self, outputfile):
        with open(outputfile, "wt") as of:
            ZeroSol = self.solution_counter(0)
            OneSol = self.solution_counter(1)
            TwoSol = self.solution_counter(2)
            ThreeSol = self.solution_counter(3)
            FourSol = self.solution_counter(4)
            InfSol = self.solution_counter("inf")
            print(f"From {self.filename}:", file=of)
            print("Equations with no solutions:", file=of)
            for eq in ZeroSol:
                print(eq, file=of)
            print("Equations with one solution:", file=of)
            for eq in OneSol:
                print(eq, file=of)
            print("Equations with two solutions:", file=of)
            for eq in TwoSol:
                print(eq, file=of)
            print("Equations with three solutions:", file=of)
            for eq in ThreeSol:
                print(eq, file=of)
            print("Equations with four solutions:", file=of)
            for eq in FourSol:
                print(eq, file=of)
            print("Equations with infinitely many solutions:", file=of)
            for eq in InfSol:
                print(eq, file=of)
            print("Equation with the smallest solution:", file=of)
            print(self.min_finder(), file=of)
            print("Equation with the largest solution:", file=of)
            print(self.max_finder(), file=of)





