CC=gcc
GFLAG=-ggdb
DEBUG=yes
CC=gcc
ifeq ($(DEBUG),yes)
	GFLAG=-ggdb
else
	GFLAG=
endif

EXEC=game
SDL_FLAGS=-lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx -ggdb 
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

$(EXEC):$(OBJ)
	@$(CC) -o  $@ $^ $(SDL_FLAGS) $(GFLAG)

%.o:%.c
	@$(CC) -o $@ -c $< $(GFLAG)

clean: 
	rm -rf *.o
mrproper:
	rm -rf $(EXEC)

