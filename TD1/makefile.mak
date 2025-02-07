#def des variables
CC = gcc
EXE = exe
INC_Dir = "header/headrs_type.h"
SRC_Dir = "progrm"
OBJ_Dir = "fich_obj"
#DATA_Dir = "chemin relatif au makefile des data"

CFLAGS = -std=c99 -Wall -pedantic  (-g) -I($INC_Dir)
#LDFLAGS = -l("lib  perso") -L("chemin d'accès lib perso") -lm

#Regle  par  défaut
default: $(EXE)

#ensemble des règles
fct.o : $(SRC_Dir)Ex1.c $(INC_Dir)headrs_type.h
	$(CC) -c $(SRC_Dir)Ex1.c

comp.o : $(SRC)main.c $(INC_Dir)headrs_type.h
	$(CC) -c $(SRC_Dir)main.c $(CFLAGS) -o $(OBJ_Dir)/comp.o

$(EXE): func.o comp.o 
	$(CC) -o $(EXE) func.o comp.o

clean:
	re -f *~ *.o $(EXE)