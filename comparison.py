#!/usr/bin/env python

'''
    Authors: 20907541, 30939506
    Due Date: 3/24/2017
'''

import subprocess
import numpy as np
import time
import random

conventionalZero = []
strassenZero = []
conventionalOne = []
strassenOne = []
conventionalTwo = []
strassenTwo = []


def matrix_generation(d):
    temporaryList = []
    for _ in range(1, 2 * d**2 + 1):
        temporaryList.append(random.randint(0, 1))
    file = open('zeroOne.txt', 'w')
    for item in temporaryList:
        file.write("%s\n" % item)

    temporaryList = []
    for _ in range(1, 2 * d**2 + 1):
        temporaryList.append(random.randint(-1, 1))
    file = open('negOnetoOne.txt', 'w')
    for item in temporaryList:
        file.write("%s\n" % item)

    temporaryList = []
    for _ in range(1, 2 * d**2 + 1):
        temporaryList.append(random.randint(-1, 1))
    file = open('onetoThree.txt', 'w')
    for item in temporaryList:
        file.write("%s\n" % item)


for d in range(1, 31):
    matrix_generation(d)
    print('matrix output for', str(d), 'created')
    # run the programs

# modify this when c code is written
# for n in ns:
#     startTime = time.time()
#     cmd = ['./randmst', "0", str(n), str(numtrials), str(dim)]
#     out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
#     endTime = time.time()
#     print n, dim
#     avg_degrees.append(float(out.split()[0]))
#     avg_time.append((endTime - startTime) / 10.)

# np.savetxt(str(dim) + '.txt', np.c_[ns, avg_degrees, avg_time])
