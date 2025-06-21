CC = gcc
CFlags = -Wall -Wextra -Wpedantic -Wpedantic -std=c18

# Main rule
all: 1dstates 2d_automat segler

# 1D cellular automats program
1dstates: 1d_states.o cell.o structs.o stepcom.o
	$(CC) $^ -o $@

1d_states.o: 1d_states.c cell.h structs.h stepcom.h
	$(CC) -c $(CFlags) $<

cell.o: cell.c cell.h structs.h
	$(CC) -c $(CFlags) $<

structs.o: structs.c structs.h
	$(CC) -c $(CFlags) $<

stepcom.o: stepcom.c stepcom.h structs.h cell.h
	$(CC) -c $(CFlags) $<

# Game of life program
2d_automat: 2d_automat.o cell.o structs.o stepcom.o
	$(CC) $^ -o $@

2d_automat.o: 2d_automat.c cell.h structs.h stepcom.h
	$(CC) -c $(CFlags) $<

# Segler program
segler: segler.o cell.o structs.o stepcom.o
	$(CC) $^ -o $@

segler.o: segler.c cell.h stepcom.h
	$(CC) -c $(CFlags) $<


run: 1dstates 2d_automat
	./1dstates
	./2d_automat
	./segler


.PHONY: all clean run
clean:
	$(RM) *.o 1dstates 2d_automat segler