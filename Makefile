OBJ     = main.o cover.o heap.o set.o dijkstra.o graph.o
CC      = g++
CFLAGS  = -m32 -O2
EXE     = assn2

findKth:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE) 

main.o: dijkstra.h graph.h set.h cover.h Makefile
dijkstra.o: dijkstra.h graph.h heap.h set.h 
graph.o: graph.h
cover.o: cover.h set.h heap.h
heap.o: heap.h
set.o: set.h

