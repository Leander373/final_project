#include "cell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // für mkdir
#include <sys/types.h>

#include "structs.h"


// Function to apply the rule to the current state
void apply_rule (cellauto *cell) {
    char new_state[cell->size];
    for (int i = 0; i < cell->size; i++) {
        int left = cell->state[(i - 1 + cell->size) % cell->size] - '0';
        int center = cell->state[i] - '0';
        int right = cell->state[(i + 1) % cell->size] - '0';
        
        // Compute new state
        if (left == 1 && center == 1 && right == 1) {
            new_state[i] = cell->rule[0];
        }
        else if (left == 1 && center == 1 && right == 0) {
            new_state[i] = cell->rule[1];
        }
        else if (left == 1 && center == 0 && right == 1) {
            new_state[i] = cell->rule[2];
        }
        else if (left == 1 && center == 0 && right == 0) {
            new_state[i] = cell->rule[3];
        }
        else if (left == 0 && center == 1 && right == 1) {
            new_state[i] = cell->rule[4];
        }
        else if (left == 0 && center == 1 && right == 0) {
            new_state[i] = cell->rule[5];
        }
        else if (left == 0 && center == 0 && right == 1) {
            new_state[i] = cell->rule[6];
        }
        else { // left == 0 && center == 0 && right == 0
            new_state[i] = cell->rule[7];
        }
    }

    // Copy new state back to original state
    for (int i = 0; i < cell->size; i++) {
        cell->state[i] = new_state[i];
    }
}


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


// Function to reset the state to a single '1' in the middle
void reset (cellauto *cell) {
    for (int i = 0; i < cell->size; i++) {
        cell->state[i] = '0';
    }

    int mid = cell->size / 2;
    cell->state[mid] = '1';
}


// Function to randomize the state
void randomize (cellauto *cell) {
    for (int i = 0; i < cell->size; i++) {
        cell->state[i] = (rand() % 2) + '0'; // Randomly set '0' or '1'
    }
}
