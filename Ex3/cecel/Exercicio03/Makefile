COMP=-c

CC=mpicc
CC_WALLTIME_FLAGS=-O3
CCFLAGS=-std=c99 $(CC_WALLTIME_FLAGS)
CCLOAD= $(CCFLAGS)

EXEC=Tempo.exe

OBJ=ModVida.o \
    WallTime.o \
    Tempo.o

all:	$(EXEC)

$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(CCLOAD) $(OBJ)

Tempo.o:	Tempo.c ModVida.o WallTime.o
	$(CC) $(COMP) $(CCFLAGS) Tempo.c

ModVida.o:	ModVida.c ModVida.h
	$(CC) $(COMP) $(CCFLAGS) ModVida.c

WallTime.o:	WallTime.c WallTime.h
	$(CC) $(COMP) $(CC_WALLTIME_FLAGS) WallTime.c

clean:
	rm -f *.o $(EXEC)


