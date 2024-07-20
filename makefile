all:
	gcc -Wall main.c Screen.h Polygon.h -lSDL2 -lSDL2main -ldl -lm
