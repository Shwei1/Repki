import math


class Figure:

    # def __init__(self, __funny, __cute):
    #     self.__funny = __funny
    #     self.__cute = __cute
    pi = math.pi

    def dimension(self):
        return None

    def perimeter(self):
        return None

    def area(self):
        return None

    def surface_area(self):
        return None

    def base_area(self):
        return None

    def height(self):
        return None

    def volume(self):
        return None


class Triangle(Figure):
    def __init__(self, a, b, c):
        sides = [a, b, c]
        sides.sort()
        a, b, c = sides
        assert a + b > c
        self.a = a
        self.b = b
        self.c = c

    def dimension(self):
        return 2

    def perimeter(self):
        return self.a + self.b + self.c

    def semiperimeter(self):
        return self.perimeter() / 2

    def area(self):
        sp = self.semiperimeter()
        return (sp * (sp - self.a) * (sp - self.b) * (sp - self.c)) ** 0.5

    def volume(self):
        return self.area()

    def __str__(self):
        return f"Triangle: a={self.a}, b={self.b}, c={self.c}"


class Rectangle(Figure):
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def perimeter(self):
        return (self.a + self.b) * 2

    def area(self):
        return self.a * self.b

    def dimension(self):
        return 2

    def volume(self):
        return self.area()

    def __str__(self):
        return f"Rectangle: a={self.a}, b={self.b}"


class Trapezium(Figure):
    def __init__(self, a, b, c, d):
        assert a != b
        # bases
        self.a = a
        self.b = b
        # sides
        self.c = c
        self.d = d

    def perimeter(self):
        return self.a + self.b + self.c + self.d

    def area(self):
        result = ((self.a + self.b) / 2) * (self.c ** 2 - (((self.a - self.b)**2 + self.c ** 2 - self.d ** 2)/(2 *(self.a - self.b)))**2)**0.5
        if isinstance(result, complex):
            complex_result = [round(result.real, 2), round(result.imag, 2)]
            result = max(complex_result)
            return result
        else:
            return round(result, 2)

    def volume(self):
        return self.area()

    def dimension(self):
        return 2

    def __str__(self):
        return f"Trapezium: a={self.a}, b={self.b}, c={self.c}, d={self.d}"


class Parallelogram(Figure):
    def __init__(self, a, b, h):
        self.a = a
        self.b = b
        self.h = h

    def perimeter(self):
        return (self.a + self.b) * 2

    def area(self):
        return self.a * self.h

    def volume(self):
        return self.area()

    def dimension(self):
        return 2

    def __str__(self):
        return f"Parallelogram: a={self.a}, b={self.b}, h={self.h}"

class Circle(Figure):

    def __init__(self, r):
        self.r = r

    def perimeter(self):
        return self.r * self.pi * 2

    def dimension(self):
        return 2

    def area(self):
        return self.pi * self.r ** 2

    def volume(self):
        return self.area()

    def __str__(self):
        return f"Circle: r={self.r}"


class Sphere(Figure):
    def __init__(self, r):
        self.r = r

    def dimension(self):
        return 3

    def height(self):
        return self.r * 2

    def volume(self):
        return (4/3) * self.pi * self.r ** 3

    def surface_area(self):
        return 4 * self.pi * self.r ** 2

    def __str__(self):
        return f"Sphere: r={self.r}"


class Tetrahedron(Triangle):
    def __init__(self, a, h):
        super().__init__(a, a, a)
        self.h = h

    def dimension(self):
        return 3
    
    def __str__(self):
        return f"Tetrahedron: a={self.a}, h={self.h}"

    def height(self):
        return self.h

    def surface_area(self):
        r = (((3) ** 0.5) / 6) * self.a
        ap = ((self.h) ** 2 * (r) ** 2) ** 0.5
        result = (3 / 2) * self.a * ap
        return result

    def base_area(self):
        return super().volume()


class QuadraticPyramid(Rectangle):
    def __init__(self, a, b, h):
        super().__init__(a, b)
        self.h = h

    def __str__(self):
        return f"Quadratic Pyramid: a={self.a}, h={self.h}"

    def dimension(self):
        return 3

    def height(self):
        return self.h

    def surface_area(self):
            halfDiag = (self.a ** 2 + self.b ** 2) ** 0.5 / 2
            edge = (halfDiag ** 2 + self.h ** 2) ** 0.5
            halfPerimeter1 = (edge * 2 + self.a) / 2
            halfPerimeter2 = (edge * 2 + self.b) / 2
            tr1 = (halfPerimeter1 * (halfPerimeter1 - self.a) * (halfPerimeter1 - edge) * (
                        halfPerimeter1 - edge)) ** 0.5
            tr2 = (halfPerimeter2 * (halfPerimeter2 - self.a) * (halfPerimeter2 - edge) * (
                        halfPerimeter2 - edge)) ** 0.5
            return 2 * tr1 + 2 * tr2

    def base_area(self):
        return super().volume()


class RectangularParallelepiped(Rectangle):
    def __init__(self, a, b, h):
        super().__init__(a, b)
        self.h = h

    def __str__(self):
        return f"Rectangular Parallelepiped: a={self.a}, b={self.b}, h={self.h}"

    def dimension(self):
        return 3

    def height(self):
        return self.h

    def surface_area(self):
        return self.h * self.a * 2 + self.h * self.b

    def volume(self):
        return self.a * self.b * self.h

    def base_area(self):
        return super().volume()


class Cone(Circle):
    def __init__(self, r, h):
        super().__init__(r)
        self.h = h

    def __str__(self):
        return f"Cone: r={self.r}, h={self.h}"

    def dimension(self):
        return 3

    def base_area(self):
        return super().volume()

    def surface_area(self):
        l = (self.r ** 2 + self.h ** 2) ** 0.5
        return math.pi * l * self.r

    def volume(self):
        return (1/3) * math.pi * (self.r ** 2) * self.h


class TriangularPrism(Triangle):
    def __init__(self, a, b, c, h):
        super().__init__(a, b, c)
        self.h = h

    def __str__(self):
        return f"Triangular Prism: a={self.a}, b={self.b}, c={self.c}, h={self.h}"

    def dimension(self):
        return 3

    def base_area(self):
        return super().volume()


    def volume(self):
        result = super().volume() * self.h
        if isinstance(result, complex):

            result_list = [round(result.real, 2), round(result.imag, 2)]
            nonComplexReslt = max(result_list)
            return nonComplexReslt
        else:

            return round(result, 2)


    def surface_area(self):
        return (self.a + self.b + self.c) * self.h













