#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "cell.h"

// Fucntions for 1d automats


// Function to apply the rule to the current state
void apply_rule (cellauto *cell) {
    char new_state[cell->size];

    // Initialize new state with the current state
    for (int i = 0; i < cell->size; i++) {
        // Get the left, center, and right neighbors
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


// Functions for 2d automats


// Function to check the number of neighbors for a cell at (row, col) in a grid of size N
int nachbar_check(int N, int row, int col, int **gitter) {
    int one_counter = 0;

    for (int i = row - 1; i < row + 2; i += 2)
    {
        for (int j = col - 1; j < col + 2; j++)
        {
            if (i > -1 && i < N && j > -1 && j < N)
            {
                if (gitter[i][j] == 1)
                {
                    one_counter++;
                }
            }
        }
    }

    for (int j = col - 1; j < col + 2; j += 2)
    {
        if (j > -1 && j < N)
        {
            if (gitter[row][j] == 1)
            {
                one_counter++;
            }
        }
    }

    return one_counter;
}


// Function to fill the grid with random values (0 or 1)
void random_auto( int **gitter, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gitter[i][j] = rand() % 2;
        }
    }
}