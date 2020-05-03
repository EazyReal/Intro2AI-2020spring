# author = yt lin
# usage  = python3 lab2-main.py < tc.txt
# tc.txt should be in format 
###
# T
# tc1 (string : "n m n_mine {grid of n*m in one line}")
# tc2
###

############################################################################

import os
import numpy as np
from copy import deepcopy
from time import time 
from colored import fg, bg, attr

# inportant references

# p by value? p by ref? p by id.
# http://dokelung.me/category/python/python-evaluation-strategy/

# deep copy
# https://ithelp.ithome.com.tw/articles/10221255

############################################################################

# macro
UNKNOWN = -1
CONSTRAINT = -2
NOMINE = 0
MINE = 1
FAIL_MSG = "leave reached but WA"

############################################################################

#here stores hyper params
TIMELIMIT = 30 #second
# forward checking
FORWARD = True
# in which order should we explore variables
MRV = True # MRV, domain smaller
DEG = True # DEG, vertex that affect more points
# limitation added if assign this value to the variable
LCV = True
GLOBALH = True
# If a variable can not be assign, do not need to try sidlings
CUTA = True

############################################################################

## board related

#board size
n = 0
m = 0
#number of mines
n_mine = 0
#maps
C = list() #constraint value
A = list() #init_board.VAR
# dx, dy can use for loop 3*3 - 0,0

############################################################################

#input the problem
# 6 6 10 -1 -1 -1 1 1 -1 -1 3 -1 -1 -1 0 2 3 -1 3 3 2 -1 -1 2 -1 -1 -1 -1 2 2 3 -1 3 -1 1 -1 -1 -1 1
test_data = [
    "4 4 5 2 -1 -1 2 -1 3 3 -1 2 2 2 1 -1 -1 -1 0",
    "6 6 10 -1 -1 -1 1 1 -1 -1 3 -1 -1 -1 0 2 3 -1 3 3 2 -1 -1 2 -1 -1 -1 -1 2 2 3 -1 3 -1 1 -1 -1 -1 1",
    "6 6 10 -1 -1 -1 1 1 1 3 4 -1 2 -1 -1 2 -1 -1 -1 -1 -1 -1 -1 2 2 -1 2 1 2 -1 -1 1 -1 -1 1 -1 1 0 -1",
    "6 6 10 -1 -1 -1 -1 -1 -1 -1 2 2 2 3 -1 -1 2 0 0 2 -1 -1 2 0 0 2 -1 -1 3 2 2 2 -1 -1 -1 -1 -1 -1 -1",
    "6 6 10 -1 1 -1 1 1 -1 2 2 3 -1 -1 1 -1 -1 5 -1 5 -1 2 -1 5 -1 -1 -1 -1 2 -1 -1 3 -1 -1 -1 1 1 -1 0"
]
#all_input = list(map(int,input().strip().split()))
def inrange(i, j):
    #global n, m
    #if(((i >= 0) and (i < n) and (j >= 0) and (j < m))):
    #     print(i, j)
    return ((i >= 0) and (i < n) and (j >= 0) and (j < m))

def printA(A):
    global n, m
    for i in range(n):
        for j in range(m):
            print(str(A[i][j]), end = " ")
        print()

# Search Node
# when n is large(>10) and constraint + variable is sparse(end of search)
# use map could be better, but for small cases that can be solved, O(n^2) should be fine
# for VAR, -1 = unassigned, -2 = constraint position, 0 = no mine, 1 = mine 

class Node:
    global n, m, C
    def __init__(self, remain=n_mine, UB=None, LB=None, VAR=None, DOM=None):
        #2D list
        self.remain = remain
        self.UB = UB
        self.LB = LB
        self.VAR = VAR
        self.DOM = DOM
        
    # use UB-LB or can use DOM len

    def calc_LCV(self, x, y):
        ret = 0
        for dx in range(-2, 3, 1):
            for dy in range(-2, 3, 1):
                nx, ny = x + dx, y + dy
                if((not (dx == 0 and dy == 0)) and inrange(nx,ny) and self.VAR[nx][ny] == UNKNOWN):
                    ret += len(self.DOM[nx][ny])
        return ret
    
    def calc_LCV0(self, x, y):
        ret = 0
        for nx in range(n):
            for ny in range(m):
                if(self.VAR[nx][ny] == CONSTRAINT):
                    #ret += len(self.DOM[nx][ny])
                    ret += self.UB[nx][ny] - self.LB[nx][ny]
        return ret
    
    # return - size of domain, because we want heuristic to be bigger => better
    def calc_MRV(self, x, y):
        return -len(self.DOM[x][y])
    
    #how many (valuabe) constraint are besides it
    def calc_DEG(self, x, y):
        ret = 0
        for dx in range(-1, 2, 1):
            for dy in range(-1, 2, 1):
                nx, ny = x + dx, y + dy
                if((not (dx == 0 and dy == 0)) and inrange(nx,ny) and self.VAR[nx][ny] == CONSTRAINT):
                    ret += int(self.UB[nx][ny] != self.LB[nx][ny])
        return ret
    
    # this is forward checking
    def check_conflict(self):
        if(self.remain < 0):
            return True
        cnt = 0
        for i in range(n):
            for j in range(m):
                # if constraint cannot be satisfy
                if(self.VAR[i][j] == CONSTRAINT and (self.UB[i][j] < C[i][j] or self.LB[i][j] > C[i][j]) ):
                    return True
                if(self.VAR[i][j] == UNKNOWN):
                    cnt += int(MINE in self.DOM[i][j])
                    if(len(self.DOM[i][j]) == 0):
                        return True
        if(self.remain > cnt):
            return True
        return False
    
    def check_AC(self):
        if(self.remain != 0): # bug, mistype == 0
            return False
        for i in range(n):
            for j in range(m):
                if(self.VAR[i][j] == UNKNOWN):
                    return False
                if(self.VAR[i][j] == CONSTRAINT):
                    cnt = 0
                    for dx in range(-1, 2, 1):
                        for dy in range(-1, 2, 1):
                            nx, ny = i + dx, j + dy
                            if((not (dx == 0 and dy == 0)) and inrange(nx,ny) and self.VAR[nx][ny] != CONSTRAINT):
                                cnt += self.VAR[nx][ny]
                    if cnt != C[i][j]:
                        return False
        return True
    
    # return a Node with value updated after assign
    def assign(self, xy, val):
        x, y = xy
        ret = deepcopy(self)
        ret.remain -= val
        ret.VAR[x][y] = val
        # change of related constraint
        for dx in range(-1, 2, 1):
            for dy in range(-1, 2, 1):
                nx, ny = x + dx, y + dy
                # for all neighbor constraints
                if((not (dx == 0 and dy == 0)) and inrange(nx,ny) and ret.VAR[nx][ny] == CONSTRAINT):
                    if(val == 0):
                        ret.UB[nx][ny] -= 1
                        if(ret.UB[nx][ny] == C[nx][ny]):
                            #ret.LB[nx][ny] = C[nx][ny] #exp, TLE
                            for dx2 in range(-1, 2, 1):
                                for dy2 in range(-1, 2, 1):
                                    nx2, ny2 = nx + dx2, ny + dy2
                                    if((not (dx2 == 0 and dy2 == 0)) and inrange(nx2,ny2) and ret.VAR[nx2][ny2] == UNKNOWN):
                                        #ret.DOM[nx2][ny2] = [x for x in ret.DOM[nx2][ny2] if x != NOMINE]
                                        ret.DOM[nx2][ny2] = [max(ret.DOM[nx2][ny2])]
                    if(val == 1):
                        ret.LB[nx][ny] += 1
                        if(ret.LB[nx][ny] == C[nx][ny]):
                            #ret.UB[nx][ny] = C[nx][ny] #exp, TLE
                            for dx2 in range(-1, 2, 1):
                                for dy2 in range(-1, 2, 1):
                                    nx2, ny2 = nx + dx2, ny + dy2
                                    if((not (dx2 == 0 and dy2 == 0)) and inrange(nx2,ny2) and ret.VAR[nx2][ny2] == UNKNOWN):
                                        #ret.DOM[nx2][ny2] = [x for x in ret.DOM[nx2][ny2] if x != MINE] 
                                        ret.DOM[nx2][ny2] = [min(ret.DOM[nx2][ny2])]
        return ret

def solve_1_CSP(id=1):
    global n, m, n_mine, C, A
    all_input = list(map(int,test_data[id].strip().split()))
    #apply input to variables
    n, m, n_mine = all_input[:3]
    flat_constraint = all_input[3:]
    C = [ [ flat_constraint[i*n+j] for j in range(m)] for i in range(n)]
    A = [[ -1 if (C[i][j] == -1) else -2 for j in range(m)] for i in range(n)]

    ### this is about init state
    def calc_init_UB(i, j, A): ## init upperbound
        ret = 0
        for dx in range(-1, 2, 1):
            for dy in range(-1, 2, 1):
                if dx == 0 and dy == 0:
                    continue
                nx, ny = i+dx, j+dy
                if(inrange(nx, ny) == True):
                    ret += int(A[nx][ny] == UNKNOWN)
        return ret
                    
    init_state = Node()   
    init_state.remain = n_mine
    init_state.UB = np.asarray([[ calc_init_UB(i, j, C) if A[i][j] == CONSTRAINT else 0 for j in range(m)] for i in range(n)])
    init_state.LB = np.asarray([[ 0 for j in range(m)] for i in range(n)])
    init_state.VAR = A #init only -1, -2 
    init_state.DOM = [[[MINE, NOMINE] for j in range(m)] for i in range(n)]

    # list() as stack, append/pop
    stack = list()
    stack.append(init_state)

    # for performance evaluation
    node_popped = 0
    node_pushed = 1
    fail_leaf = 0
    start_t = time()
    time_elasped = 0

    # final result
    ans_node = Node()

    #IMPORTANT!!! stack is Last in First out
    while(len(stack)):
        # pop node
        cur = stack[-1]
        stack.pop(-1)
        node_popped += 1
        
        #if not forward checking, check when pop out here
        if(not FORWARD):
            if(cur.check_conflict()):
                continue

        # add children to todo
        todo = list()
        for i in range(n):
            for j in range(m):
                if(cur.VAR[i][j] == UNKNOWN):
                    mrv = cur.calc_MRV(i, j) if MRV else 0
                    deg = cur.calc_DEG(i, j) if DEG else 0
                    todo.append((mrv, deg, (i,j)))
        
        # debug msg
        if(node_popped % 100 == 0):
            print("Node pushed", node_pushed)
            print("Node popped", node_popped)
            printA(cur.VAR)
            time_passed = time() - start_t
            if( time_passed > TIMELIMIT):
                print("TLE with time limit {}".format(TIMELIMIT))
                break
        
        # No children, done all assignments, check if AC
        if(len(todo) == 0):
            if(not cur.check_AC()): 
                print(FAIL_MSG)
                fail_leaf += 1
                continue
            else:
                ans_node = cur
                break
        
        # Start Assignments by heuristic, first MVC, then DEG
        #todo.sort(reverse=True)
        todo.sort(reverse=False)
        #False with MRV DEG is quicker =>
        #desireto too see negative MRV nigger first and degree bigger first
        topush = []
        FAILA = False
        for mcv_h, deg_h, (nx, ny) in todo:
            # LCV heuristic
            # the one with greater dimension of freedom explore first
            nxt = []
            for val in cur.DOM[nx][ny]: # 0, 1
                nxti = cur.assign((nx, ny), val)
                if(FORWARD and nxti.check_conflict()):
                    continue
                if(LCV):
                     h = nxti.calc_LCV0(nx, ny) # constant of 25cells
                elif(GLOBALH):
                     h = int((val == MINE and len(todo)/2 < cur.remain) or (val == NOMINE and len(todo)/2 >= cur.remain) )
                node_pushed += 1
                nxt.append((nxti, h))
                
            if(CUTA):
                if(len(nxt) == 0):
                    FAILA = True
                    break
            #nxt.sort(key=lambda x :x[1], reverse=True) # try smaller LSV, earlier pop
            nxt.sort(key=lambda x :x[1], reverse=False) # bigger LCV, later insertion, earlier exlporation
            for nxtnode, h_ in nxt:
                topush.append(nxtnode)
        
        if(CUTA and FAILA):
            node_pushed -= len(topush)
            continue
        else:
            stack.extend(topush)

    #end of CSP solver
    end_t = time()
    time_elasped = end_t - start_t

    print(ans_node.VAR)

    return ans_node, node_pushed, node_popped, time_elasped

def print_statistics(ANS, node_pushed, node_popped, time_elasped):
    global A, C
    print("Node pushed", node_pushed)
    print("Node popped", node_popped)
    print("time elasped", time_elasped)
    printA(C)
    print()

    if(time_elasped < TIMELIMIT):
        # combine rule and result
        final_board = [
            [ str(C[i][j]) if A[i][j]==-2 else ".x"[ANS.VAR[i][j]] for j in range(m)] for i in range(n)
        ]

        # print with color 
        for i in range(n):
            for j in range(m):
                print("%s"%(fg(1)) if A[i][j] != -2 else "", final_board[i][j], "%s"%(attr(0))if A[i][j] != -2 else "", end=' ')
            print()

if __name__ == "__main__":
    solve = int(input())
    ans_node, node_pushed, node_popped, time_elasped = solve_1_CSP(solve)
    print_statistics(ans_node, node_pushed, node_popped, time_elasped)