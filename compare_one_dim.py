#!/usr/bin/env python

'''
    Authors: 20907541, 30939506
    Due: 3/24/2017 at 5 pm
'''

import subprocess
import time
import random

# use this to change what dimension is being timed
dimension = 1024


def matrix_generation(d):
    print 'file generation started'
    file = open('cod_testfile2.txt', 'w')
    startTime = time.time()
    # create file with matrix that has values -1, 0, 1
    for i in range(1, 2 * d**2 + 1):
        file.write("%s\n" % random.randint(-1, 1))
    file.close()
    endTime = time.time()
    timeResult = endTime - startTime
    print 'file generation complete'
    print 'time taken:', timeResult


# run process
def test_process(flag):
    print 'flag', str(flag), 'testing starting'
    # start time
    startTime = time.time()
    # ./programname flag dimension inputfile
    cmd = ['./main', str(flag), 'compare_one_dim_testfile.txt']
    # run command
    out, err = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()
    # end time
    endTime = time.time()
    # add time to average
    timeResult = (endTime - startTime)
    # show progress
    print 'flag', str(flag), 'time:', timeResult


# generate the file
matrix_generation(dimension)
# flag 1
#test_process(1)
# flag 2
#test_process(2)
