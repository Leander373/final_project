// Header for computing and printing steps into files
#ifndef STEPCOM_H
#define STEPCOM_H

#include "structs.h"

void steps(cellauto *cell);

void fileprint_auto(int** gitter, int size, int steps);

#endif