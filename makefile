#def des variables
CC = gcc
EXE = exe
INC_Dir = header
SRC_Dir_td1 = TD1
OBJ_Dir = fich_obj
#DATA_Dir = "chemin relatif au makefile des data"

CFLAGS = -std=c99 -pedantic  -g -I$(INC_Dir)
#LDFLAGS = -l("lib  perso") -L("chemin d'accès lib perso") -lm

#Regle  par  défaut
default: $(EXE)

#ensemble des règles
$(OBJ_Dir)/fct.o : $(SRC_Dir_td1)/Ex1.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir)/Ex1.c $(CFLAGS) -o $(OBJ_Dir)/fct.o

$(OBJ_Dir)/fct2.o : $(SRC_Dir_td1)/Ex2.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir)/Ex2.c $(CFLAGS) -o $(OBJ_Dir)/fct2.o

$(OBJ_Dir)/comp.o : main.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir)/main.c $(CFLAGS) -o $(OBJ_Dir)/comp.o

$(EXE): $(OBJ_Dir)/fct.o $(OBJ_Dir)/fct2.o $(OBJ_Dir)/comp.o 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ_Dir)/fct.o $(OBJ_Dir)/fct2.o $(OBJ_Dir)/comp.o

clean:
	rm -f $(OBJ_Dir)/*.o n*.ppm .pgm