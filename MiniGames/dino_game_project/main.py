import random
import turtle

# Screen setup
wn = turtle.Screen()
wn.title("DINO")
wn.bgcolor("white")
wn.setup(width=900, height=400)
wn.tracer(0)

#scoreboard
pen = turtle.Turtle()
pen.speed(0)
pen.shape("square")
pen.color("black")
pen.penup()
pen.hideturtle()
pen.goto(0, 100)
pen.write("Player A: 0  Player B: 0", align="center", font=("Courier", 10 , "normal"))

#ground
ground = turtle.Turtle()
ground.penup()
ground.goto(-450, -80)
ground.pendown()
ground.fd(910)

# dino
dino = turtle.Turtle()
dino.shape("circle")
dino.color("grey")
dino.penup()
dino.goto(-330, -80)

# cacti adding function
cacti = []
dx = 0.15
# def add_cacti():
# cactus 1
cactus1 = turtle.Turtle()
cactus1.shape("square")
cactus1.color("grey")
cactus1.penup()
cac_start_x = 450
cactus1.goto(cac_start_x, -80)
cactus1_stat = True

def jump():
    y = dino.ycor()
    y += 100
    dino.sety(y)

# keypress
wn.listen()
wn.onkeypress(jump, "s")

# game loop
while True:
    wn.update()

    score_a = 0 
    score_b= 0
    pen.clear()
    pen.write("Player A: {}  Player B: {}".format(score_a, score_b), align="center", font=("Courier", 24, "normal")) 
           
    if cactus1_stat == True:    
        cac_start_x -= dx
        cactus1.goto(cac_start_x, -80)
    
    # dino.sety(-80)    
    