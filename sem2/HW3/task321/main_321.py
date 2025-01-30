from HW3.task321.eqreader import Output

files = ("input01.txt", "input02.txt", "input03.txt")

# print(Output("input01.txt").solution_counter("inf"))

# for file in files:
#     print(Output(file).show())

if __name__ == '__main__':
    for file in files:
        f = Output(file)
        f.output(f"output{files.index(file)+1}.txt")



