import turtle


tina = turtle.Turtle()
tina.shape('turtle')
tina.pencolor("#ff0000")
tina.color("#ff0000","#cc66cc")
tina.begin_fill()
for j in range(8, 0, -1):
    for i in range(0, 4, 1):
        tina.forward((200 * (1 + 0)))
        tina.left(90)
    tina.left(45)

turtle.done()