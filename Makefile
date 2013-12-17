CC=gcc
OBJECTS= list.o file.o graphic.o 

essai : $(OBJECTS)
	$(CC) $(OBJECTS) -o essai -lm

list.o : list.c list.h 
	$(CC) -c list.c

file.o : file.c file.h 
	$(CC) -c file.c

graphic.o : graphic.c list.h file.h 
	$(CC) -c graphic.c

clean :
	rm -f *~ *.o \#*\# essai
