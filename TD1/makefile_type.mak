#def des variables
CC = gcc
EXE = exe
INC_Dir = "chemin relatif au makefile des headers"
SRC_Dir = "chemin relatif au makefile des programmes"
OBJ_Dir = "chemin relatif au makefile des objets"
DATA_Dir = "chemin relatif au makefile des data"

CFLAGS = -std=c99 -Wall -pedantic  (-g) -I($INC_Dir)
LDFLAGS = -l("lib  perso") -L("chemin d'accès lib perso") -lm

#Regle  par  défaut
default: $(EXE)

#ensemble des règles
func.o : func.c func.h
	$(CC) -c func.c

comp.o : main.c func.h
	$(CC) -c main.c $(CFLAGS) -o $(OBJ_Dir)/comp.o

$(EXE): func.o comp.o 
	$(CC) -o $(EXE) func.o comp.o

clean:
	re -f *~ *.o $(EXE)