#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Own headers with function declarations, structs etc. 
#include "structs.h"
#include "cell.h"
#include "stepcom.h"


int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return 1;
    }

    // User input for size and iterations
    int size = atoi(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Error: Size must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    int iterations = atoi(argv[2]);

    // Initialize state
    cellauto *cell = malloc(sizeof(cellauto));
    if (!cell) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    cell->state = malloc(size * sizeof(char));
    if (!cell->state) {
        fprintf(stderr, "Error: Memory allocation for state failed.\n");
        free(cell);
        return EXIT_FAILURE;
    }
    cell->rule = NULL; 
    cell->rule_name = 0;
    cell->rand = false;
    cell->iterations = iterations;
    cell->size = size;


    reset(cell); // Initialize state with a single '1' in the middle
    cell->rule = RULE_22;
    cell->rule_name = 22;

    // Compute steps for not random initial condition
    steps(cell);
    reset(cell); 
    cell->rule = RULE_106;
    cell->rule_name = 106;

    steps(cell);
    reset(cell); 
    cell->rule = RULE_187;
    cell->rule_name = 187;

    steps(cell);
    reset(cell); 
    cell->rule = RULE_214;
    cell->rule_name = 214;

    steps(cell);
    reset(cell); 


    // Now random states
    cell->rand = true;

    // Set random initial state
    srand(time(NULL)); // Seed for random number generation
    randomize(cell);
    cell->rule = RULE_22;
    cell->rule_name = 22;

    // Compute steps for random initial condition
    steps(cell);
    randomize(cell); 
    cell->rule = RULE_106;
    cell->rule_name = 106;

    steps(cell);
    randomize(cell); 
    cell->rule = RULE_187;
    cell->rule_name = 187;

    steps(cell);
    randomize(cell); 
    cell->rule = RULE_214;
    cell->rule_name = 214;

    steps(cell);

    // Free allocated memory
    free(cell->state);
    free(cell);

    return EXIT_SUCCESS;
}
