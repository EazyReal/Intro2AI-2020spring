# author = yt lin
# usage = python3 testcase_generator.py < 6 6 10 100

import os 
import numpy as np
import random

## hyper params 

n = 6 
m = 6
nv = 10
n_mine = 0

## use input
n, m, nv, N = list(map(int,input().strip().split()))

## init all positions
all_coordinate = []
for i in range(n):
    for j in range(m):
        all_coordinate.append((i,j))

def inrange(i, j):
    return i >= 0 and i < n and j >= 0 and j < m

def gen(n, m, nv):
    n_mine = 0
    ## pick variable positions
    POSV = random.sample(all_coordinate, nv)
    MARK = [[ 0 for j in range(m)] for i in range(n)]
    for pos in POSV:
        MARK[pos[0]][pos[1]] = 1
    # variables
    A = [[ random.choice([0,1]) if MARK[i][j] else -1 for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            n_mine += int(A[i][j] == 1)
    # constraints init
    B = [[ 0 for j in range(m)] for i in range(n)]
    # calc constraints
    for i in range(n):
        for j in range(m):
            if A[i][j] == -1:
                for di in range(-1, 2, 1):
                    for dj in range(-1, 2, 1):
                        if(not (di == dj and di == 0) and inrange(i+di, j+dj)):
                            B[i][j] += int(A[i+di][j+dj] == 1)
    TC = [[ B[i][j] if A[i][j] == -1 else -1  for j in range(m)] for i in range(n)]
    SAMPLE_ANS = [[ B[i][j] if A[i][j] == -1 else "ox"[A[i][j]]  for j in range(m)] for i in range(n)]
    return n, m, n_mine, TC, SAMPLE_ANS


def create_tc_file(n, m, nvar, ntc):
    with open("testcase_" + str(n) + "_" +  str(m) + "_" + str(nvar) + "_" + str(ntc) + ".txt", "w") as fo:
        for i in range(ntc):
            n, m, n_mine, TC, SAMPLE_ANS = gen(m, m, nvar)
            TC_str = str(n) + " " +  str(m) + " " + str(n_mine)
            for i in range(n):
                for j in range(m):
                    TC_str += " " + str(TC[i][j])
            fo.write(TC_str)
            fo.write("\n")

create_tc_file(n, m, nv, N)




