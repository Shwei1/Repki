from reader import Reader

def ChampSeeker(fayl):
    reader = Reader(fayl)
    shapes = reader.read()
    maxPerArea = [0, 0]
    maxshape = shapes[0]
    for shape in shapes:
        if shape.perimeter() > maxPerArea[0] and shape.area() > maxPerArea[1]:
            maxPerArea = [shape.perimeter(), shape.area()]
            maxshape = shape
    print(f"The largest shape is {maxshape}, its perimeter is {maxPerArea[0]} and its area is {maxPerArea[1]}")
if "__main__" == __name__:
    for name in ["input01.txt", "input02.txt", "input03.txt"]:
        ChampSeeker(name)




