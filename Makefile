tsnake : main.o snake.o fruit.o body.o point.o
	gcc --std=c11 -o tsnake main.o snake.o fruit.o body.o point.o -lncurses
main.o : main.c snake.h fruit.h
	gcc --std=c11 -c main.c
snake.o : snake.c snake.h fruit.h body.h
	gcc --std=c11 -c snake.c
fruit.o : fruit.c fruit.h point.h
	gcc --std=c11 -c fruit.c
body.o : body.c body.h point.h
	gcc --std=c11 -c body.c
point.o : point.c point.h
	gcc --std=c11 -c point.c

clean :
	rm tsnake main.o snake.o fruit.o body.o point.o
