from reader import Output
files = ["input01.txt", "input02.txt", "input03.txt"]
for filename in files:
    f = Output(filename)
    f.output(f"output{files.index(filename)+1}.txt")