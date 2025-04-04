#def des variables

CC = gcc
EXE = exe
INC_Dir = header
SRC_Dir = TD1
SRC_Dir2 = TD2
SRC_Dir3 = TD3

OBJ_Dir = fich_obj
#DATA_Dir = "chemin relatif au makefile des data"

CFLAGS = -std=c99 -pedantic -g -I$(INC_Dir) -lm

#LDFLAGS = -l("lib  perso") -L("chemin d'accès lib perso") -lm

#Regle  par  défaut
default: $(EXE)

#ensemble des règles
$(OBJ_Dir)/fct.o : $(SRC_Dir)/Ex1.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir)/Ex1.c $(CFLAGS) -o $(OBJ_Dir)/fct.o $(CFLAGS)

$(OBJ_Dir)/fct2.o : $(SRC_Dir)/Ex2.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir)/Ex2.c $(CFLAGS) -o $(OBJ_Dir)/fct2.o $(CFLAGS)

$(OBJ_Dir)/fct3.o : $(SRC_Dir)/Ex3.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir)/Ex3.c $(CFLAGS) -o $(OBJ_Dir)/fct3.o $(CFLAGS)

$(OBJ_Dir)/fct4.o : $(SRC_Dir2)/Ex1.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir2)/Ex1.c $(CFLAGS) -o $(OBJ_Dir)/fct4.o $(CFLAGS)

$(OBJ_Dir)/fct5.o : $(SRC_Dir2)/Ex2.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir2)/Ex2.c $(CFLAGS) -o $(OBJ_Dir)/fct5.o $(CFLAGS)

$(OBJ_Dir)/comp.o : $(SRC_Dir3)/main.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir3)/main.c $(CFLAGS) -o $(OBJ_Dir)/comp.o $(CFLAGS)

$(OBJ_Dir)/fct6.o : $(SRC_Dir3)/Ex1.c $(INC_Dir)/headrs_type.h
	$(CC) -c $(SRC_Dir3)/Ex1.c $(CFLAGS) -o $(OBJ_Dir)/fct6.o $(CFLAGS)

$(EXE): $(OBJ_Dir)/fct.o $(OBJ_Dir)/fct2.o $(OBJ_Dir)/fct3.o $(OBJ_Dir)/fct4.o $(OBJ_Dir)/fct5.o $(OBJ_Dir)/fct6.o $(OBJ_Dir)/comp.o 
	$(CC) -o $(EXE) $(OBJ_Dir)/fct.o $(OBJ_Dir)/fct2.o $(OBJ_Dir)/fct3.o $(OBJ_Dir)/fct4.o $(OBJ_Dir)/fct5.o $(OBJ_Dir)/fct6.o $(OBJ_Dir)/comp.o $(CFLAGS)

clean:
	rm -f $(OBJ_Dir)/*.o n*.ppm .pgm