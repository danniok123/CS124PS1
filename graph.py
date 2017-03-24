#!/usr/bin/env python

# Authors: 20907541, 30939506
# Due: 3/24/2017 at 5 pm

import numpy as np
import subprocess
import random
import matplotlib.pyplot as plt

# matrix file
matrixFile = 'crossover_matrix.txt'

# dimensions to test
ns = [x for x in xrange(1, 1025)]
# bounds for matrix value ranges (integer values)
low = -1
high = 1
# flag
flag = 0


# create matrix file
def matrix_generation(d, l, h):
    file = open(matrixFile, 'w')
    for _ in xrange(1, 2 * d**2 + 1):
        file.write("%s\n" % random.randint(l, h))
    file.close()


# run process
def test_process(flag, d, c):
    # ./programname flag dimension inputfile crossover_value
    cmd = ['./main', str(flag), str(d), matrixFile, str(c)]
    # run command
    out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
    return out


# store threshold for each dimension
thresholds = []
# runtimes = []
for n in ns:
    # generate matrix
    matrix_generation(n, low, high)
    # run the program across all possible thresholds
    if n < 100:
        thresholds.append(test_process(0, n, n))
    else:
        thresholds.append(test_process(0, n, 100))
    print str(n), 'complete'
# generate scatter plot of thresholds
N = 50
x = ns
y = thresholds
plt.scatter(x, y, alpha=0.5)
plt.show()
