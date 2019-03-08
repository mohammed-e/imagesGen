CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=drawer
FILE1=vector_graphic_1


all: $(EXEC) 



drawer: drawer.o list.o save.o user.o batch.o
	$(CC) -o drawer drawer.o list.o save.o user.o batch.o $(LDFLAGS)


drawer.o: drawer.c 
	$(CC) -o drawer.o -c drawer.c $(CFLAGS)


batch.o: batch.c batch.h
	$(CC) -o batch.o -c batch.c $(CFLAGS)


user.o: user.c user.h
	$(CC) -o user.o -c user.c $(CFLAGS)


save.o: save.c save.h
	$(CC) -o save.o -c save.c $(CFLAGS)


list.o: list.c list.h
	$(CC) -o list.o -c list.c $(CFLAGS)


draw:
	./$(EXEC)


convert:
	./$(EXEC) $(FILE1)



clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)


