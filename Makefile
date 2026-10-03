CC = gcc
CFLAGS = -Wall -Wextra

inverted.o : main.o Database.o function.o Display.o Save.o Clear.o Search.o Update.o
	$(CC) $(CFLAGS) main.o Database.o function.o Save.o Display.o Clear.o Search.o Update.o -o inverted.o
main.o : function.h
	$(CC) $(CFLAGS) -c main.c
Database.o : function.h 
	$(CC) $(CFLAGS) -c Database.c
function.o : function.h
	$(CC) $(CFLAGS) -c function.c
Display.o : function.h
	$(CC) $(CFLAGS) -c Display.c
Save.o : function.h
	$(CC) $(CFLAGS) -c Save.c
Clear.o : function.h
	$(CC) $(CFLAGS) -c Clear.c
Search.o : function.h
	$(CC) $(CFLAGS) -c Search.c
Update.o : function.h
	$(CC) $(CFLAGS) -c Update.c 	

clean :
	rm -f *.o inverted.o

