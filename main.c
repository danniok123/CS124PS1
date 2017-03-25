/*
    Authors: 20907541, 30939506
    Due Date: 3/24/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

#define threshold 90


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
            m[i][j] = rand() % 3;
        }
    }

    return m;
}

// Included in neg so that it's not necessary to create subtraction func
int **add_matrix(int **a, int **b, int d, int neg) {

    int **c = newMatrix(d);
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            c[i][j] = a[i][j] + neg * b[i][j];
        }
    }

    return c;
}


int **standardmult(int **a, int **b, int **c, int d) {
    //int **c = newMatrix(d);
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < d; k++) {
                c[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return c;
}

// Freeing the matrix
void freeMatrix(int d, int **a) {
    for (int i = 0; i < d; i++) {
        free(a[i]);
    }

    free(a);
}

int **strassen(int **x, int **y, int **z, int dim) {
    if (dim == 1) {
        z[0][0] = x[0][0] * y[0][0];
        return z;
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


        strassen(a, add_matrix(f, h, half, -1), p1, half); // A(F − H)
        strassen(add_matrix(a, b, half, 1), h, p2, half); // (A + B)H
        strassen(add_matrix(c, d, half, 1), e, p3, half); // (C + D)E
        strassen(d, add_matrix(g, e, half, -1), p4, half); // D(G - E)
        strassen(add_matrix(a, d, half, 1), add_matrix(e, h, half, 1), p5, half); // (A + D)(E + H)
        strassen(add_matrix(b, d, half, -1), add_matrix(g, h, half, 1), p6, half); // (B - D)(G + H)
        strassen(add_matrix(a, c, half, -1), add_matrix(e, f, half, 1), p7, half); // (A - C)(E + F)

        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                // AE + BG = P5 + P4 - P2 + P6
                z[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j]; 
                // AF + BH = P1 + P2
                z[i][j + half] = p1[i][j] + p2[i][j];
                // CE + DG = P3 + P4 
                z[i + half][j] = p3[i][j] + p4[i][j]; 
                // CF + DH = P5 + P1 - P3 - P7
                z[i + half][j + half] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j]; 
            }
        }

        freeMatrix(half, b); freeMatrix(half, d);
        freeMatrix(half, f); freeMatrix(half, h);
        freeMatrix(half, p1); freeMatrix(half, p2); freeMatrix(half, p3); freeMatrix(half, p4);
        freeMatrix(half, p5); freeMatrix(half, p6); freeMatrix(half, p7);
        return z;

    }
}


// Strassen's algorithm
int **strassenMod(int **x, int **y, int **z, int dim) {

    //int **z = newMatrix(dim);
    
    if (dim <= threshold)
        return standardmult(x, y, z, dim);

    else if (dim == 1) {
        z[0][0] = x[0][0] * y[0][0];
        return z;
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


        strassenMod(a, add_matrix(f, h, half, -1), p1, half); // A(F − H)
        strassenMod(add_matrix(a, b, half, 1), h, p2, half); // (A + B)H
        strassenMod(add_matrix(c, d, half, 1), e, p3, half); // (C + D)E
        strassenMod(d, add_matrix(g, e, half, -1), p4, half); // D(G - E)
        strassenMod(add_matrix(a, d, half, 1), add_matrix(e, h, half, 1), p5, half); // (A + D)(E + H)
        strassenMod(add_matrix(b, d, half, -1), add_matrix(g, h, half, 1), p6, half); // (B - D)(G + H)
        strassenMod(add_matrix(a, c, half, -1), add_matrix(e, f, half, 1), p7, half); // (A - C)(E + F)

        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                // AE + BG = P5 + P4 - P2 + P6
                z[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j]; 
                // AF + BH = P1 + P2
                z[i][j + half] = p1[i][j] + p2[i][j];
                // CE + DG = P3 + P4 
                z[i + half][j] = p3[i][j] + p4[i][j]; 
                // CF + DH = P5 + P1 - P3 - P7
                z[i + half][j + half] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j]; 
            }
        }

        freeMatrix(half, b); freeMatrix(half, d);
        freeMatrix(half, f); freeMatrix(half, h);
        freeMatrix(half, p1); freeMatrix(half, p2); freeMatrix(half, p3); freeMatrix(half, p4);
        freeMatrix(half, p5); freeMatrix(half, p6); freeMatrix(half, p7);
        return z;

    }
}

// Padding 
int padding(int d) {
    int tmp = d;
    while (tmp > threshold) {
        tmp = (tmp + 1) / 2;
    }

    while (tmp < d) {
        tmp *= 2;
    }

    return tmp;
}

void printDiags(int d, int **a) {
    for (int i = 0; i < d; i++){
        printf("%d\n", a[i][i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    // Error Handling
    if (argc != 4) {
        printf("Format is: ./strassen flag dimension inputfile");
        return 1;
    }

    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);

    int old = dimension;
    clock_t t1, t2;

    FILE *file;

    file = fopen(argv[3], "r");

    if (dimension > 2) {
        dimension = padding(dimension);
    }

    int **a = newMatrix(dimension);
    int **b = newMatrix(dimension);
    int **c = newMatrix(dimension);

    // Takes care of padding for first matrix
    for (int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(i < old && j< old){
                fscanf(file, "%d", &a[i][j]);
            }
            else{
                a[i][j]=0;
            }
        }
    }

    // Takes care of padding for second matrix
    for (int i = 0; i < dimension; i++){
        for(int j =0; j < dimension; j++){
            if(i < old && j< old){
                fscanf(file, "%d", &b[i][j]);
            }
            else{
                b[i][j]=0;
            }
        }
    }

    if (flag == 1) {
        t1 = clock();
        for (int x = 0; x < 10; x++) {
            c = strassenMod(a, b, c, dimension);
        }
        t1 = clock() - t1;
        double secs = ((double)t1) / CLOCKS_PER_SEC;
        double time1 = secs / 10;
        printf("strassenMod() took an average of %f seconds \n", time1);
    }

    if (flag == 2) {
        t2 = clock();
        for (int x = 0; x < 10; x++) {
            c = standardmult(a, b, c, old);
        }
        t2 = clock() - t2;
        double secs2 = ((double)t2) / CLOCKS_PER_SEC;
        double time2 = secs2 / 10;
        printf("standardmult() took an average of %f seconds \n", time2);
    }
    
    c = strassenMod(a, b, c, dimension);

    printDiags(old, c);

    freeMatrix(dimension, a);
    freeMatrix(dimension, b);
    freeMatrix(dimension, c);

    return 0;
}
