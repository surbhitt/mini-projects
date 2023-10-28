CC=clang
FLAGS=-Wno-missing-braces -Wall -Wextra -ggdb -std=c99 -pedantic -lraylib -lGL -lm

rope_sim: rope_sim.c
	$(CC) rope_sim.c -o out_rope_sim $(FLAGS)
clean:
	rm out_*
