// Header file for cellular automata structures
#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>

// Rules
extern const char RULE_22[8];
extern const char RULE_106[8];
extern const char RULE_187[8];
extern const char RULE_214[8];

// Struct for states and rules
typedef struct {
    char *state;
    // Rules are represented as strings of 8 characters
    const char *rule;  
    int rule_name;
    bool rand; // Random initial condition
    // Provided by input
    int iterations;  // Number of iterations
    int size;  // Size of the state
} cellauto;

#endif