#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // for mkdir

#include "stepcom.h"
#include "cell.h"

// Fucntions for 1d automats


// Function for computing iterated steps
void steps(cellauto *cell) {
    // 1. Check if the folder exists, do not create a new one
    struct stat st;
    if (stat("1d_plots", &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: Folder '1d_plots' does not exist.\n");
        exit(1);
    }

    // 2. Build the filename: e.g., "1d_plots/1d_rule_187.txt" for different states
    char filename[256];
    if (!cell->rand) {
        snprintf(filename, sizeof(filename),
             "1d_states/1d_rule_%d.txt",
             cell->rule_name);
    }
    else {
        snprintf(filename, sizeof(filename),
             "1d_states/1d_rule_%d_random.txt",
             cell->rule_name);
    }

    // 3. Open the file for writing
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    // 4. Example: write the initial state
    for (int i = 0; i < cell->size; i++) {
        fputc(cell->state[i], file);
        if (i + 1 < cell->size) fputc(' ', file);   
    }
    fputs("\n", file);

    // 5. Iteration loop to apply the rule and write the states
    for (int it = 1; it < cell->iterations; it++) {
        // Apply rule
        apply_rule(cell);
        // Write the new state to the file
        for (int i = 0; i < cell->size; i++) {
            fputc(cell->state[i], file);
            if (i + 1 < cell->size) fputc(' ', file);
        }
        fputs("\n", file);
    }

    fclose(file);
}


// Functions for 2d automats


// Funtion for prinitng the states into files
void fileprint_auto(int** gitter, int size, int steps) {
    for (int t = 0; t < steps; t++)
    {
        int temp[size][size];
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (gitter[i][j] == 1)
                {
                    if (nachbar_check(size, i, j, gitter) < 2)
                    {
                        temp[i][j] = 0;
                    }
                    else if (nachbar_check(size, i, j, gitter) > 3)
                    {
                        temp[i][j] = 0;
                    }
                    else
                    {
                        temp[i][j] = 1;
                    }
                }
                else
                {
                    if (nachbar_check(size, i, j, gitter) == 3)
                    {
                        temp[i][j] = 1;
                    }
                    else
                    {
                        temp[i][j] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                gitter[i][j] = temp[i][j];
            }
        }

        FILE *file;

        char filename[50];
        snprintf(filename, sizeof(filename), "2d_states/2d_state_%04d.txt", t + 1);

        file = fopen(filename, "w");

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                fprintf(file, "%d ", gitter[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}
