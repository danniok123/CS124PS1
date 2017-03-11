/*
    Authors: 20907541, 30939506
    Due Date: 3/24/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>

// read in the test file and generate two matrices
// 2d^2 total lines
void graphGeneration() {
    // read in file
    return false;
}

// calculate runtime of algorithm
void runtime() {
    return false;
}

// Strassen's algorithm
void strassen() {
    return false;
}

// Standard multiplication algorithm
void standard() {
    return false;
}

int main(int argc, char const *argv[]) {
    // declare variables to avoid scoping issues
    int dimension = 0;
    filename = "default"

    // user-defined arguments
    if (argc == 3) {
        // number of dimensions
        dimension = atoi(argv[1])
        // filename
        filename = argv[2]
    } else {
        printf("Invalid Input; Please pass dimension and test file")
    }

    // create matrices
    graphGeneration();

    // run Strassen's algorithm
    strassen();

    // run standard algorithm
    standard();
}