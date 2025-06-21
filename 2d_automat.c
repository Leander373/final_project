#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Self created headers
#include "cell.h"
#include "structs.h"
#include "stepcom.h"


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Falsche Parameteranzahl, zwei werden benötigt!\n");
        printf("Gittergröße und Anzahl der Zeitschritte\n");
        exit(1);
    }

    int N = atof(argv[1]);
    int M = atof(argv[2]);

    srand(time(NULL));

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


    // Initialize the grid with random values
    random_auto((int **)gitter, N);


    // Compute time steps
    fileprint_auto((int **)gitter, N, M);


    // Free the allocated memory
    for (int i = 0; i < N; i++) {
        free(gitter[i]);
    }
    free(gitter);

    return 0;
}