/*
    Authors: 20907541, 30939506
    Due Date: 3/24/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#include "main.h"



/* Function that generates a random
   matrix with dimension d
*/
matrix *genrandMatrix(int d) {
    //time_t t;
    //srand(time(NULL));

    matrix *m = (matrix *) malloc(sizeof(matrix));
    m->row = 0;
    m->col = 0;
    m->d = d;
    m->data = malloc(d * sizeof(int*));
    for (int i = 0; i < d; i++) {
        m->data[i] = malloc(d * sizeof(int*));
    }

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            int num = rand() % 3;
            m->data[i][j] = num; 
        }
    }

    return m;
}


matrix *add_matrix(matrix *a, matrix *b, matrix *c) {

    for (int i = 0; i < a->d; i++) {
        for (int j = 0; j < a->d; j++) {
            c->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }

    return c;
}

matrix *sub_matrix(matrix *a, matrix *b, matrix *c) {

    for (int i = 0; i < a->d; i++) {
        for (int j = 0; j < a->d; j++) {
            c->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }

    return c;
}

void standardmult(matrix *a, matrix *b, matrix *c) {
    for (int i = 0; i < a->d; i++) {
        for (int j = 0; j < a->d; j++) {
            for (int k = 0; k < b->d; k++) {
                c->data[i][k] += a->data[i][j] * b->data[j][k];
            }
        }
    }
}

// Freeing the matrix
void freeMatrix(matrix* m) {
    for (int i = 0; i < m->d; i++) {
        free(m->data[i]);
    }

    free(m->data);
    free(m);
}

// read in the test file and generate two matrices
// 2d^2 total lines
void graphGeneration() {
    // read in file
    //return false;
}

// calculate runtime of algorithm
void runtime() {
    //return false;
}

// Strassen's algorithm
void strassen() {
    //return false;
}

// Standard multiplication algorithm
void standard() {
    //return false;
}

int main(int argc, char const *argv[]) {

    // Error Handling
    if (argc != 4) {
        printf("Format is: ./strassen flag dimension inputfile");
        return 1;
    }

    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);

    // create matrices
    graphGeneration();

    // run Strassen's algorithm
    strassen();

    // run standard algorithm
    standard();
}