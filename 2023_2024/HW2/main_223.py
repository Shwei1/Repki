from random import randint
import tkinter
from Triangle import generateTriangles

triangle = generateTriangles(1)[0]

key = int(input("Choose your animation: \n1) Rotation"
            "\n2) Deformation\n"))


if key == 1:
        while True:
            triangle.draw()
            triangle.set_rotation(10)
            (x1, y1), (x2, y2) = triangle.rotated_vertices()
            triangle.__init__(x1, y1, x2, y2)
            triangle.cleaner()
elif key == 2:
    while True:
        triangle.draw()
        triangle.set_distortion(1.05, 1.05)
        (x1, y1), (x2, y2) = triangle.stretched_vertices()
        triangle.__init__(x1, y1, x2, y2)
        triangle.cleaner()

tkinter.mainloop()

