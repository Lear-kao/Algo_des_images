#def des variables
CC = gcc
EXE = exe

#Regle  par  défaut
default: $(EXE)

#ensemble des règles
func.o : func.c func.h
	$(CC) -c func.c

comp.o : main.c func.h
	$(CC) -c main.c

$(EXE): func.o comp.o 
	$(CC) -o $(EXE) func.o comp.o

clean:
	re -f *~ *.o $(EXE)