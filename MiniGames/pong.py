
import turtle


# screen setup
wn = turtle.Screen()
wn.title("PONG")
wn.bgcolor("black")
wn.setup(width=800, height=600)
wn.tracer(0)

# scoreboard
score_a = 0
score_b = 0
scoreboard = turtle.Turtle()
scoreboard.speed(0)
scoreboard.penup()
scoreboard.speed(0)
scoreboard.shape("square")
scoreboard.color("white")
scoreboard.goto(0, 260)
scoreboard.hideturtle()
scoreboard.write("Player A: 0 Player B: 0", align="center", font=("Courier", 15, "normal"))

# paddle a (left one) graphics
paddle_a = turtle.Turtle()
paddle_a.speed(0)
paddle_a.shape("square")
paddle_a.color("white")
paddle_a.shapesize(stretch_wid=5, stretch_len=0.7)
paddle_a.penup()
paddle_a.goto(-350, 0)

# paddle b (right one) graphics
paddle_b = turtle.Turtle()
paddle_b.speed(0)
paddle_b.shape("square")
paddle_b.color("white")
paddle_b.shapesize(stretch_wid=5, stretch_len=0.7)
paddle_b.penup()
paddle_b.goto(350, 0)

# ball graphics
ball = turtle.Turtle()
ball.speed(0)
ball.shape("circle")
ball.color("white")
ball.penup()
ball.goto(0, 0)
ball.dx = 0.15
ball.dy = 0.15

# functions
def paddle_a_up():
    y = paddle_a.ycor()
    y += 20
    paddle_a.sety(y) 

def paddle_a_down():
    y = paddle_a.ycor()
    y -= 20
    paddle_a.sety(y)

def paddle_b_up():
    y = paddle_b.ycor()
    y += 20
    paddle_b.sety(y)

def paddle_b_down():
    y = paddle_b.ycor()
    y -= 20
    paddle_b.sety(y)

# keybindings
wn.listen()
wn.onkeypress(paddle_a_up, "w")
wn.onkeypress(paddle_a_down, "s")
wn.onkeypress(paddle_b_up, "Up")
wn.onkeypress(paddle_b_down, "Down")

# main game loop
while True:
    wn.update()

    # ball movement
    ball.setx(ball.xcor() + ball.dx)
    ball.sety(ball.ycor() + ball.dy)

    # border checking
    # top and bottom
    if ball.ycor() > 290:
        ball.sety(290)
        ball.dy *= -1
    elif ball.ycor() < -290:
        ball.sety(-290)
        ball.dy *= -1

    # sides
    if ball.xcor() > 350:
        score_a +=1
        scoreboard.clear()
        scoreboard.write("Player A: {} Player B: {}".format(score_a, score_b), align="center", font=("Courier", 15, "normal"))
        ball.goto(0, 0)
        ball.dx *= -1

    elif ball.xcor() < -350:
        score_b += 1
        scoreboard.clear()
        scoreboard.write("Player A: {} Player B: {}".format(score_a, score_b), align="center", font=("Courier", 15, "normal"))
        ball.goto(0, 0)
        ball.dx *= -1   

    # paddle and ball collision
    if ball.xcor() < -340 and ball.ycor() < paddle_a.ycor() + 50 and ball.ycor() > paddle_a.ycor() - 50:
        ball.dx *= -1
    elif ball.xcor() > 340 and ball.ycor() < paddle_b.ycor() + 50 and ball.ycor() > paddle_b.ycor() - 50:
        ball.dx *= -1    




# ... ..- .-. -... .... .. -