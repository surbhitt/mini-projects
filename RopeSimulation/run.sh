set -xe
CC="clang"
FLAGS="-Wno-missing-braces -Wall -Wextra -ggdb -std=c99 -pedantic -lraylib -lGL -lm"

$CC rope_sim.c -o out_rope_sim $FLAGS
./out_rope_sim
