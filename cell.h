// Header for initializing and manipulating a cellular automats
#ifndef CELL_H
#define CELL_H

#include "structs.h"

void apply_rule (cellauto *cell);

void reset (cellauto *cell);

void randomize (cellauto *cell);

int nachbar_check(int N, int row, int col, int **gitter);

void random_auto( int **gitter, int size);

#endif
