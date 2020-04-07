game:main.o entite_secondaire.o background.o
	gcc main.o entite_secondaire.o background.o -o game -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c
	gcc -c main.c
entite_secondaire.o:entite_secondaire.c
	gcc -c entite_secondaire.c
background.o:background.c
	gcc -c background.c