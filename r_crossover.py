#!/usr/bin/env python
# Authors: 20907541, 30939506
# Due: 3/24/2017 at 5 pm

import subprocess
import numpy as np
import time
import random

# matrix file
matrixFile = 'r_crossover_matrix.txt'

# dimensions to test
ns = [x for x in xrange(1, 257)]
# bounds for matrix value ranges (integer values)
low = -1
high = 1
# number of trials
trials = 5


# create matrix file
def matrix_generation(d, l, h):
    file = open(matrixFile, 'w')
    for _ in xrange(1, 2 * d**2 + 1):
        file.write("%s\n" % random.randint(l, h))
    file.close()


# run process
def test_process(flag, d, c):
    startTime = time.time()
    # ./program_name flag dimension inputfile crossover_value
    cmd = ['./main', str(flag), str(d), matrixFile, str(c)]
    # run command
    out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
    endTime = time.time()
    timeResult = endTime - startTime
    return timeResult


# calculate which crossover point results in fastest algo runtime
best_c = []
best_t = []
for n in ns:
    # store runtime of algorithm w/ each crossover point
    runtime = []
    # generate matrix
    matrix_generation(n, low, high)
    # calculate strassen variant runtime for each crossover point value
    if n < 100:
        for i in xrange(1, n + 1, 5):
            totalTime = 0
            for _ in range(0, trials):
                totalTime += test_process(0, n, i)
            runtime.append(totalTime / float(trials))
    else:
        for i in xrange(1, 101, 5):
            totalTime = 0
            for _ in range(0, trials):
                totalTime += test_process(0, n, i)
            runtime.append(totalTime / float(trials))
    # fastest runtime
    best_t.append(min(runtime))
    # optimal crossover point
    best_c.append(runtime.index(min(runtime)) * 5 + 1)
    print str(n), 'complete'
result = np.column_stack((ns, best_c, best_t))
np.savetxt('r_crossover.txt', result)
print 'r_crossover.py is done running'
