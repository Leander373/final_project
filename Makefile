CC = gcc
CFlags = -Wall -Wextra -Wpedantic -Wpedantic -std=c18

# Main rule
all: 1dstates 2d_automat

1dstates: 1d_states.o cell.o structs.o
	$(CC) $^ -o $@

1d_states.o: 1d_states.c cell.h structs.h
	$(CC) -c $(CFlags) $<

cell.o: cell.c cell.h structs.h
	$(CC) -c $(CFlags) $<

structs.o: structs.c structs.h
	$(CC) -c $(CFlags) $<

2d_automat: 2d_automat.o 
	$(CC) $^ -o $@

2d_automat.o: 2d_automat.c 
	$(CC) -c $(CFlags) $<


run: 1dstates 2dstates
	./1dstates
	./2d_automat

.PHONY: all clean run
clean:
	$(RM) *.o 1dstates 2d_automat