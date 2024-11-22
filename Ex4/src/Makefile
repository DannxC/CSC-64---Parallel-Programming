# para versao 4.5 do OMP, usar "module load gcc/11.1" no SDumont
CC=gcc
COMP=-c
CC_WALL_TIME_FLAGS=-O3
CC_FLAGS=$(CC_WALL_TIME_FLAGS) -std=c99 -fopenmp
#CC_LOAD= -lm

EXEC=Pipe.exe

OBJ=\
	WallTime.o \
	Main.o

all:	$(EXEC)


$(EXEC):	$(OBJ)
	$(CC) $(CC_FLAGS) -o $(EXEC) $(OBJ) $(CC_LOAD)

WallTime.o:	WallTime.c WallTime.h
	$(CC) $(COMP) $(CC_WALL_TIME_FLAGS) WallTime.c

Main.o:	Main.c Pipe.h WallTime.o
	$(CC) $(COMP) $(CC_FLAGS) Main.c

clean:
	rm -f *.o $(EXEC)
