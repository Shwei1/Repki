from math import pi

class Triangle:
    def __init__(self, a, b, c):
        self.a = float(a)
        self.b = float(b)
        self.c = float(c)
    def perimeter(self):
        return self.a + self.b + self.c
    def area(self):
        s = self.perimeter()/2
        return (s * (s - self.a)*(s - self.b)*(s - self.c)) ** 0.5


class Rectangle:
    def __init__(self, width, height):
        self.width = width
        self.height = height
    def perimeter(self):
        return 2 * (self.width + self.height)
    def area(self):
        return self.width * self.height

class Trapeze:
    def __init__(self, base1, base2, side3, side4):
        self.base1 = base1
        self.base2 = base2
        self.side3 = side3
        self.side4 = side4
    def perimeter(self):
        return self.base1 + self.base2 + self.side3 + self.side4
    def area(self):
        try:
            area_ = ((self.base1 + self.base2) / 2) * (self.side3 ** 2 - (((self.base1 - self.base2)**2 + self.side3 ** 2 - self.side4 ** 2)/(2 * (self.base1 - self.base2)))**2) ** 0.5
        except ZeroDivisionError:
            area_ = 0
        return area_


class Parallelogram:
    def __init__(self, a, b, h):
        self.a = a
        self.b = b
        self.h = h
    def perimeter(self):
        return 2 * (self.a + self.b)
    def area(self):
        return self.a * self.h

class Circle:
    def __init__(self, radius):
        self.r = radius
    def perimeter(self):
        return 2*pi*self.r
    def area(self):
        return pi * (self.r)**2

