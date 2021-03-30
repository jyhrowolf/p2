CC = g++
OBJ = main.cpp
HEADER = defn.h
CFLAGS = -c -Wall -I

myAppStore:
	$(CC) $(OBJ) -o $@
main.o: main.cpp $(HEADER)
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm -rf *o myAppStore