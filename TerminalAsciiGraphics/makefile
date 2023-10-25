
CC=clang
C+=clang++

all: bouncing_ball img_ascii terminal_fps

bouncing_ball: bouncing_ball.c
	$(CC) bouncing_ball.c -o out_bouncing_ball 

img_ascii: img_ascii.c
	$(CC) img_ascii.c -o out_img_ascii -lm

terminal_fps: TerminalFPS.cpp
	$(C+) TerminalFPS.cpp -o out_terminal_fps -I header/stb_image.h

clean: 
	rm *.out out_*
