from random import randint
from Triangle import generateTriangles
import tkinter
triangles = generateTriangles(100)
for triangle in triangles:
    bound = 100
    triangle.set_position(randint(-bound, bound), randint(-bound, bound))
    triangle.draw()

tkinter.mainloop()
