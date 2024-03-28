from classes import Circle, Rectangle, Parallelogram, Trapeze, Triangle
class Reader:
    def __init__(self, filename):
        self.filename = filename
    def read(self):
        shapes = []
        with open(self.filename) as f:
            for line in f:
                data = line.split()
                type = data[0]
                try:
                    if type == "Triangle":
                        a, b, c = [float(val) for val in data[1:]]
                        triangle = Triangle(a, b, c)
                        shapes.append(triangle)
                    if type == "Triangle":
                        a, b, c = [float(el) for el in data[1:]]
                        triangle = Triangle(a, b, c)
                        shapes.append(triangle)
                    elif type == "Rectangle":
                        a, b = [float(el) for el in data[1:]]
                        rectangle = Rectangle(a, b)
                        shapes.append(rectangle)
                    elif type == "Parallelogram":
                        a, b, h = [float(el) for el in data[1:]]
                        parallelogram = Parallelogram(a, b, h)
                        shapes.append(parallelogram)
                        pass
                    elif type == "Circle":
                        r = float(data[1])
                        circle = Circle(r)
                        shapes.append(circle)
                        pass
                    elif type == "Trapeze":
                        a, b, c, d = [float(el) for el in data[1:]]
                        trapeze = Trapeze(a, b, c, d)
                        shapes.append(trapeze)
                    elif type == "Circle":
                        r = float(data[1])
                        circle = Circle(r)
                        shapes.append(circle)
                except AssertionError:
                    pass

        return shapes