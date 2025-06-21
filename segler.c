#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stepcom.h"
#include "cell.h"


int main()
{
    int N = 200;
    int M = 200;

    // Dynamically create array
    int **gitter = malloc(N * sizeof(int *));
    if (gitter == NULL)
    {
        fprintf(stderr, "Memory allocation failed for grid.\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        gitter[i] = malloc(N * sizeof(int));
        // Handle error correctly
        if (gitter[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for grid row %d.\n", i);
            for (int j = 0; j < i; j++)
            {
                free(gitter[j]);
            }
            free(gitter);
            exit(1);
        }
    }

    // Initialize gitter with 0's
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            gitter[i][j] = 0;
        }
    }

    // Spaceship
    int raumschiff[4][5] = {
        {0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0}};

    // Place the spaceship in the grid
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            gitter[i + 98][j + 150] = raumschiff[i][j];
        }
    }

    // Compute time steps
    fileprint_auto(gitter, N, M);

    // Free the allocated memory
    for (int i = 0; i < N; i++) {
        free(gitter[i]);
    }
    free(gitter);

    return 0;
}