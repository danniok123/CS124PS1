#!/usr/bin/env python
# Authors: 20907541, 30939506
# Due: 3/24/2017 at 5 pm

# dimension
DIM = 285
# file
matrixFile = 'generated_matrix' + str(DIM) + '.txt'


# create matrix file
def matrix_generation(d):
    file = open(matrixFile, 'w')
    for _ in xrange(1, d**2 + 1):
        file.write("%s\n" % 1)
    for _ in xrange(1, d**2 + 1):
        file.write("%s\n" % 2)
    file.close()


matrix_generation(DIM)
