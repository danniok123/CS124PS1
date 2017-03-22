#!/usr/bin/env python

'''
    Authors: 20907541, 30939506
    Due: 3/24/2017 at 5 pm
'''

import subprocess
import numpy as np
import time
import random

# matrix file
matrixFile = 'comparison_matrix.txt'

# dimensions to test
ns = [x for x in xrange(1, 2049)]
# bounds for matrix value ranges (integer values)
low = -1
high = 1
# number of trials per dimension
trials = 5


# create matrix file
def matrix_generation(d, l, h):
    file = open(matrixFile, 'w')
    for _ in xrange(1, 2 * d**2 + 1):
        file.write("%s\n" % random.randint(l, h))
    file.close()


# run process
def test_process(flag):
    startTime = time.time()
    # ./programname flag dimension inputfile
    cmd = ['./main', str(flag), matrixFile]
    # run command
    out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
    endTime = time.time()
    timeResult = endTime - startTime
    return timeResult


# avg time list for each flag
avg1_time = []
avg2_time = []
for n in ns:
    avg1 = 0
    avg2 = 0
    for _ in xrange(0, trials):
        # create the text file
        matrix_generation(n, low, high)
        avg1 = test_process(1) + avg1
        avg2 = test_process(2) + avg2
    # add average time to each
    avg1_time.append(avg1 / 5.)
    avg2_time.append(avg2 / 5.)
    # show progress
    print 'dimension', str(n), 'complete'

result1 = np.column_stack((ns, avg1_time))
result2 = np.column_stack((ns, avg2_time))
np.savetxt('comparison_flag1.txt', result1)
np.savetxt('comparison_flag2.txt', result2)
print 'comparison.py is now exiting'
