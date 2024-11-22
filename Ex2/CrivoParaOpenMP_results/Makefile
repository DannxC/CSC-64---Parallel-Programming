CC=gcc
COMP=-c
CC_WALL_TIME_FLAGS=-O3
CC_FLAGS=$(CC_WALL_TIME_FLAGS) -std=c99 -fopenmp
CC_LOAD= -lm

EXEC=Primos.exe

OBJ=\
	WallTime.o \
	Marcador.o \
	Crivo.o \
	main.o

all:	$(EXEC)


$(EXEC):	$(OBJ)
	$(CC) $(CC_FLAGS) -o $(EXEC) $(OBJ) $(CC_LOAD)

WallTime.o:	WallTime.c
	$(CC) $(COMP) $(CC_WALL_TIME_FLAGS) WallTime.c

Marcador.o:	Marcador.c Marcador.h
	$(CC) $(COMP) $(CC_FLAGS) Marcador.c

Crivo.o:	Crivo.c Crivo.h Marcador.o
	$(CC) $(COMP) $(CC_FLAGS) Crivo.c

main.o:	main.c Crivo.o Marcador.o WallTime.h
	$(CC) $(COMP) $(CC_FLAGS) main.c

clean:
	rm -f *.o $(EXEC)
