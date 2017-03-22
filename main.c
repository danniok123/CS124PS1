/*
    Authors: 20907541, 30939506
    Due Date: 3/24/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include "main.h"

#define threshold 256


int **newMatrix(int d) {
    int **m = (int**) malloc(d * sizeof(int*));

    // allocating memory for each row in the matrix
    for (int i = 0; i < d; i++){
        m[i] = (int *) calloc(d, sizeof(int));
    }

    return m;
}

/* Function that generates a random
   matrix with dimension d
   For testing purposes
*/
int **genrand_Matrix(int d) {
    //time_t t;
    //srand(time(NULL));

    int **m = newMatrix(d);

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            m[i][j] = rand() % 100; // 0 - 99
        }
    }

    return m;
}

// Included in neg so that it's not necessary to create subtraction func
int **add_matrix(int **a, int **b, int **c, int d, int neg) {
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            c[i][j] = a[i][j] + neg * b[i][j];
        }
    }
    return c;
}

// Included in neg so that it's not necessary to create subtraction func
int **add(int **a, int **b, int **c, int d, int neg) {
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            c[i][j] = a[i][j] + neg * b[i][j];
        }
    }
    return c;
}

// Conventional matrix multiplication
void standardmult(int **a, int **b, int **c, int d) {
    //int **c = newMatrix(d);
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < d; k++) {
                c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        }
    }
}

// Freeing the matrix
void freeMatrix(int d, int **a) {
    for (int i = 0; i < d; i++) {
        free(a[i]);
    }

    free(a);
}

void newZ(int **x, int **z, int d, int n) {
  for (int i = 0; i< d; i++){
    for (int j = 0; i< d; i++){
        if (n == 1)
            z[i][j] = x[i][j];
        else if (n == 2)
            z[i][j + d] = x[i][j];
        else if (n == 3)
            z[i + d][j] = x[i][j];
        else if (n == 4)
            z[i + d][j + d] = x[i][j];
    }
  }
}


// Strassen's Modified algorithm
void strassenMod(int **x, int **y, int **z, int dim) {
    
    if (dim <= threshold)
        standardmult(x, y, z, dim);

    else if (dim == 1) {
        z[0][0] = x[0][0] * y[0][0];
    }

    else {
        int half = dim / 2;
        int **a, **c, **e, **g;

        
        int **b = newMatrix(half);
        int **d = newMatrix(half);
        int **f = newMatrix(half);
        int **h = newMatrix(half);

        int **p1 = newMatrix(half);
        int **p2 = newMatrix(half);
        int **p3 = newMatrix(half);
        int **p4 = newMatrix(half);
        int **p5 = newMatrix(half);
        int **p6 = newMatrix(half);
        int **p7 = newMatrix(half);

        int **tmp1 = newMatrix(half);
        int **tmp2 = newMatrix(half);

        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                b[i][j] = x[i][j + half];
                d[i][j] = x[i + half][j + half];
                f[i][j] = y[i][j + half];
                h[i][j] = y[i + half][j + half];
            }
        }

        a = x;
        c = &x[half];

        e = y;
        g = &y[half];

        strassenMod(a, add_matrix(f, h, tmp1, half, -1), p1, half); // A(F - H)
        strassenMod(add_matrix(a, b, tmp1, half, 1), h, p2, half); // (A + B)H
        strassenMod(add_matrix(c, d, tmp1, half, 1), e, p3, half); // (C + D)H
        strassenMod(d, add_matrix(g, e, tmp1, half, -1), p4, half); // D(G - E)
        strassenMod(add_matrix(a, d, tmp1, half, 1), add_matrix(e, h, tmp2, half, 1), p5, half); // (A + D)(E + H)
        strassenMod(add_matrix(b, d, tmp1, half, -1), add_matrix(g, h, tmp2, half, 1), p6, half); // (B - D)(G + H)
        strassenMod(add_matrix(a, c, tmp1, half, -1), add_matrix(e, f, tmp2, half, 1), p7, half); // (A - C)(E + F)

        // AE + BG = P5 + P4 - P2 + P6
        add_matrix(p5, p4, tmp1, half, 1);
        add_matrix(tmp1, p2, tmp2, half, -1);
        add_matrix(tmp2, p6, tmp1, half, 1);
        newZ(tmp1, z, half, 1);

        // AF + BH = P1 + P2
        add_matrix(p1, p2, tmp2, half, 1);
        newZ(tmp2, z, half, 2);

         // CE + DG = P3 + P4
        add_matrix(p3, p4, tmp1, half, 1);
        newZ(tmp1, z, half, 3);

        add_matrix(p5, p1, tmp1, half, 1);
        add_matrix(tmp1, p3, tmp2, half, -1);
        add_matrix(tmp2, p7, tmp1, half, -1);
        newZ(tmp1, z, half, 4);


        freeMatrix(half, b); freeMatrix(half, d); freeMatrix(half, f); freeMatrix(half, h);
        freeMatrix(half, tmp1); freeMatrix(half, tmp2); freeMatrix(half, p1); freeMatrix(half, p2); 
        freeMatrix(half, p3); freeMatrix(half, p4); freeMatrix(half, p5);  freeMatrix(half, p6);  
        freeMatrix(half, p7);   
    }
}

// Pad to the nearest power of 2
int padding(int d) {

    int p = 1;

    while(p < d)
        p *= 2;

    return p;
}

// Print the diagonals of the matrix
void printDiags(int d, int **a) {
// only print the diagonals, ignore the paddings
    for (int i = 0; i < d; i++){
        if (a[i][i] == 0)
            continue;
        printf("%d\n", a[i][i]);
    }

    printf("\n");
}


// testing standard matrix mult on small dimension
void test1(int **a, int **b, int **c, int d) {
    //assert(standardmult);


}

int main(int argc, char *argv[]) {

    // Error Handling
    if (argc != 4) {
        printf("Format is: ./strassen flag dimension inputfile");
        return 1;
    }

    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    clock_t t1;

    int old = dimension;

    FILE *file;

    file = fopen(argv[3], "r");

    if (dimension > 2) {
        dimension = padding(dimension);
    }

    int **a = newMatrix(dimension);
    int **b = newMatrix(dimension);
    int **c = newMatrix(dimension);

    // Takes care of padding for first matrix
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if (i < old && j< old){
                fscanf(file, "%d", &a[i][j]);
            }

            // pad the rest with 0's
            else{
                a[i][j]=0;
            }
        }
    }

    // Takes care of padding for second matrix
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if (i < old && j< old){
                fscanf(file, "%d", &b[i][j]);
            }

            // pad the rest with 0's
            else{
                b[i][j]=0;
            }
        }
    }

    /*for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            printf("%d\n", a[i][j]);
        }
    }*/

    if (flag == 1) {
        a = genrand_Matrix(dimension);
        b = genrand_Matrix(dimension);
        t1 = clock();
        standardmult(a, b, c, dimension);
        t1 = clock() - t1;
        double fib1 = ((double)t1) / CLOCKS_PER_SEC;
        printf("recfib() took %f seconds \n", fib1);
        //printDiags(dimension, c);
    }

    /*if (flag == 2) {
        a = genrand_Matrix(dimension);
        b = genrand_Matrix(dimension);
        t1 = clock();
        strassen(a, b, c, dimension);
        t1 = clock() - t1;
        double fib1 = ((double)t1) / CLOCKS_PER_SEC;
        printf("recfib() took %f seconds \n", fib1);
        //printDiags(dimension, c);
    }*/
    

    t1 = clock();
    strassenMod(a, b, c, dimension);
    t1 = clock() - t1;
    double fib1 = ((double)t1) / CLOCKS_PER_SEC;
    printf("recfib() took %f seconds \n", fib1);

    //printDiags(dimension, c);

    freeMatrix(dimension, a);
    freeMatrix(dimension, b);
    freeMatrix(dimension, c);

    fclose(file);

    return 0;
}