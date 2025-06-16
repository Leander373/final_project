#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>   // für mkdir
#include <sys/types.h>

// Rules
const char RULE_22[8] = {'0', '0', '0', '1', '0', '1', '1', '0'}; // 22 in binary
const char RULE_106[8] = {'0', '1', '1', '0', '1', '0', '1', '0'}; // 106 in binary
const char RULE_187[8] = {'1', '0', '1', '1', '1', '0', '1', '1'}; // 187 in binary
const char RULE_214[8] = {'1', '1', '0', '1', '0', '1', '1', '0'}; // 214 in binary


// Function to apply the rule to the current state
void apply_rule (const char *rule, char *state, int size) {
    char new_state[size];
    for (int i = 0; i < size; i++) {
        int left = state[(i - 1 + size) % size] - '0';
        int center = state[i] - '0';
        int right = state[(i + 1) % size] - '0';
        
        // Compute new state
        if (left == 1 && center == 1 && right == 1) {
            new_state[i] = rule[0];
        }
        else if (left == 1 && center == 1 && right == 0) {
            new_state[i] = rule[1];
        }
        else if (left == 1 && center == 0 && right == 1) {
            new_state[i] = rule[2];
        }
        else if (left == 1 && center == 0 && right == 0) {
            new_state[i] = rule[3];
        }
        else if (left == 0 && center == 1 && right == 1) {
            new_state[i] = rule[4];
        }
        else if (left == 0 && center == 1 && right == 0) {
            new_state[i] = rule[5];
        }
        else if (left == 0 && center == 0 && right == 1) {
            new_state[i] = rule[6];
        }
        else { // left == 0 && center == 0 && right == 0
            new_state[i] = rule[7];
        }
    }

    // Copy new state back to original state
    for (int i = 0; i < size; i++) {
        state[i] = new_state[i];
    }
}


// Function for computing iterated steps
void steps(char *state, int size, int iterations, const char *rule, const int rule_name, bool rand) {
    // 1. Check if the folder exists, do not create a new one
    struct stat st;
    if (stat("1d_plots", &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: Folder '1d_plots' does not exist.\n");
        exit(1);
    }

    // 2. Build the filename: e.g., "1d_plots/1d_rule_187.txt" for different states
    char filename[256];
    if (!rand) {
        snprintf(filename, sizeof(filename),
             "1d_states/1d_rule_%d.txt",
             rule_name);
    }
    else {
        snprintf(filename, sizeof(filename),
             "1d_states/1d_rule_%d_random.txt",
             rule_name);
    }

    // 3. Open the file for writing
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    // 4. Example: write the initial state
    for (int i = 0; i < size; i++) {
        fputc(state[i], file);
        if (i + 1 < size) fputc(' ', file);   
    }
    fputs("\n", file);

    // 5. Iteration loop to apply the rule and write the states
    for (int it = 1; it < iterations; it++) {
        // Apply rule
        apply_rule(rule, state, size);
        // Write the new state to the file
        for (int i = 0; i < size; i++) {
            fputc(state[i], file);
            if (i + 1 < size) fputc(' ', file);
        }
        fputs("\n", file);
    }

    fclose(file);
}

void reset (char *state, int size) {
    for (int i = 0; i < size; i++) {
        state[i] = '0';
    }

    int mid = size / 2;
    state[mid] = '1';
}

void randomize (char *state, int size) {
    for (int i = 0; i < size; i++) {
        state[i] = (rand() % 2) + '0'; // Randomly set '0' or '1'
    }
}



int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int iterations = atoi(argv[2]);

    char *state = malloc(size * sizeof(char));
    if (!state) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    reset(state, size); // Initialize state with a single '1' in the middle

    // Compute steps for not random initial condition
    steps(state, size, iterations, RULE_22, 22, false);
    reset(state, size); // Reset state for next rule

    steps(state, size, iterations, RULE_106, 106, false);
    reset(state, size); // Reset state for next rule

    steps(state, size, iterations, RULE_187, 187, false);
    reset(state, size); // Reset state for next rule

    steps(state, size, iterations, RULE_214, 214, false);
    reset(state, size); // Reset state for next rule


    // Set random initial state
    srand(time(NULL)); // Seed for random number generation
    randomize(state, size);

    // Compute steps for random initial condition
    steps(state, size, iterations, RULE_22, 22, true);
    randomize(state, size); // Reset state for next rule

    steps(state, size, iterations, RULE_106, 106, true);
    randomize(state, size); // Reset state for next rule

    steps(state, size, iterations, RULE_187, 187, true);
    randomize(state, size); // Reset state for next rule

    steps(state, size, iterations, RULE_214, 214, true);
    
    free(state);
}