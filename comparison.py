#!/usr/bin/env python

'''
    Authors: 20907541, 30939506
    Due: 3/24/2017 at 5 pm
'''

import subprocess
import numpy as np
import time
import random

# files
files = ['zeroOne.txt', 'negOnetoOne.txt', 'onetoThree.txt']

# dimensions to test
ns = [2**x for x in range(0, 12)] + [2**x + 1 for x in range(0, 12)]
# trials per dimension
numtrials = 10
# average time
avg_time = []


def matrix_generation_zero(d):
    # create file with matrix that has values 0, 1
    temporaryList = []
    for _ in range(1, 2 * d**2 + 1):
        temporaryList.append(random.randint(0, 1))
    file = open(files[0], 'w')
    for item in temporaryList:
        file.write("%s\n" % item)


def matrix_generation_one(d):
    # create file with matrix that has values -1, 0, 1
    temporaryList = []
    for _ in range(1, 2 * d**2 + 1):
        temporaryList.append(random.randint(-1, 1))
    file = open(files[1], 'w')
    for item in temporaryList:
        file.write("%s\n" % item)


def matrix_generation_two(d):
    # create file with matrix that has values 1, 2, 3
    temporaryList = []
    for _ in range(1, 2 * d**2 + 1):
        temporaryList.append(random.randint(1, 3))
    file = open(files[2], 'w')
    for item in temporaryList:
        file.write("%s\n" % item)

# flag 1
for n in ns:
    # intiialize avg to zero
    avg = 0
    # run each dimension 10 times
    for time in range(0, 10):
        # start time
        startTime = time.time()
        # ./programname flag dimension inputfile
        cmd = ['./main', str(i), files[0]]
        # run command
        out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
        # end time
        endTime = time.time()
        # add time to average
        avg = (endTime - startTime) + avg
    # add average time to list
    avg_time.append(avg / 10.)
    # show progress
    print ('flag', str(i), 'dimension', str(n) + '*' + str(n), 'complete')


np.savetxt('conventional' + '.txt', np.c_[ns, avg_time])

# flag 2
for n in ns:
    # intiialize avg to zero
    avg = 0
    # run each dimension 10 times
    for time in range(0, 10):
        # start time
        startTime = time.time()
        # ./programname flag dimension inputfile
        cmd = ['./main', '2', files[0]]
        # run command
        out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
        # end time
        endTime = time.time()
        # add time to average
        avg = endTime - startTime + avg
    # add average time
    avg_time.append(avg)
    # show progress
    print ('flag 2', 'dimension', str(n) + '*' + str(n), 'complete')

np.savetxt('strassen' + '.txt', np.c_[ns, avg_time])
