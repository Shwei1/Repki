from turtle import *
from random import randint
from math import pi, sin, cos, radians


class Triangle:
    def __init__(self, x1, y1, x2, y2):
        self.__position = (0, 0)
        self.__vertex1 = (x1, y1)
        self.__vertex2 = (x2, y2)
        self.__colour = "red"

    def set_position(self, x, y):
        self.__position = (x, y)

    def set_colour(self, colour):
        self.__colour = colour

    def set_rotation(self, angle):
        self.__angle = angle

    def set_distortion(self, dist_x, dist_y):
        self.__dist_x = dist_x
        self.__dist_y = dist_y

    def rotated_vertices(self):
        self.__angle = radians(self.__angle)
        self.__vertex1 = [cos(self.__angle) * (self.__vertex1[0] - self.__position[0]) - sin(self.__angle) * (self.__vertex1[1] - self.__position[1]) + self.__position[0],
                          sin(self.__angle) * (self.__vertex1[0] - self.__position[0]) + cos(self.__angle) * (self.__vertex1[1] - self.__position[1]) + self.__position[1]]
        self.__vertex2 = [cos(self.__angle) * (self.__vertex2[0] - self.__position[0]) - sin(self.__angle) * (self.__vertex2[1] - self.__position[1]) + self.__position[0],
                          sin(self.__angle) * (self.__vertex2[0] - self.__position[0]) + cos(self.__angle) * (self.__vertex2[1] - self.__position[1]) + self.__position[1]]
        return self.__vertex1, self.__vertex2

    def stretched_vertices(self):
        self.__vertex1 = [self.__position[0] + (self.__vertex1[0] - self.__position[0]) * self.__dist_x, self.__position[1] + (self.__vertex1[1] - self.__position[1]) * self.__dist_y]

        self.__vertex2 = [self.__position[0] + (self.__vertex2[0] - self.__position[0]) * self.__dist_x, self.__position[1] + (self.__vertex2[1] - self.__position[1]) * self.__dist_y]
        return self.__vertex1, self.__vertex2

    def draw(self):
        speed(0)
        setpos(self.__position[0], self.__position[1])
        pencolor(self.__colour)
        fillcolor(self.__colour)
        begin_fill()
        down()
        goto(self.__vertex1[0], self.__vertex1[1])
        goto(self.__vertex2[0], self.__vertex2[1])
        goto(self.__position[0], self.__position[1])
        end_fill()
        up()

    def cleaner(self):
        clear()








def generateTriangles(number):
        colours = [
            "green yellow",
            "teal",
            "deep pink",
            "rosy brown",
            "red",
            "green",
            "black",
            "dark olive green",
            "cyan",
            "cornflowerblue"
        ]

        bound = 350
        triangles = []
        for i in range(number):
            x1 = randint(-bound, bound)
            y1 = randint(-bound, bound)
            x2 = randint(-bound, bound)
            y2 = randint(-bound, bound)
            triangle = Triangle(x1, y1, x2, y2)
            color_num = randint(0, len(colours) - 1)
            triangle.set_colour(colours[color_num])
            triangles.append(triangle)
        return triangles
