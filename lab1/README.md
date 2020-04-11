---
title: Intro to AI lab1
tag: lab, intro2AI, NCTU, 2020
author: Yan-Tong Lin, 0712238@NCTU
usage: Intro2AI lab1
IDE: VSCode
Compile Option: g++ game.cpp -o out -std=c++17
Version Control: github
Repo Link: https://github.com/EazyReal/Intro2AI-2020spring
copy right: All right reserves. No copy, No plagiarism!!!
last update: 4/11 22:37
---

# Intro to AI lab1

## Information
- author: Yan-Tong Lin, 0712238@NCTU
- usage: Intro2AI lab1
- development tools:
    - IDE: VSCode
    - Compile Option: g++ game.cpp -o out -std=c++17
    - Version Control: [github](https://github.com/EazyReal/Intro2AI-2020spring)
- copy right: All right reserves. No copy, No plagiarism!!!
- last update: 3/30 17:27

## Usage of Program(for README.md)
-  game.cpp is for interavtive testing
    -  compile and run
    - ```g++ -o out -std=c++17 game.cpp```
    - ``` ./out```
-  exp.sh is for experiments
    -  ```./exp.sh $max_board_size $delta_board_size $test_case_number```
        -  this will kill and make new testcases and results folders containning testcases and results of algorithms
    -  detail
        -  generate testcases with tc_generate.sh 
        -  rm -rf and mkdir results
        -  compile and run exp.cpp
    -  to modify the algorithms or add features
        -  refer to <algorithm_solver>.hpp
-  game.cpp/exp.cpp < "solvers.hpp" < "custum.hpp" < <bits/stdc++.h>

Note:
- both usage is only tested on Mac OS
- to improve random property, please use other library, it is said that bash $RANDOM is not random enough

## Task Description
- the problem: 
    - find a path for Ma chess from s to t
![](https://i.imgur.com/M1gIWYH.png =50%x)
- implement BFS/DFS/IDDFS/A*/IDA*
- for A*/IDA*
    - try difference heuristic
- run experiments(decide by ourself)
    - different N(ex:4, 8, 12, 20)
        - todo: random test case generator and feeder
    - record time/space and draw as graph 
        - todo: c++ plotting, c++ memory tracing
- bonus: other heuristics
    - try to use max(h1, h2) technique
    - observe how can it move best

## My Bonus
- OOP style implementation
    - BFS_solver, etc. inherit solver
    - proper use of reference and pointer
- Experiments with shell script and exp.cpp
- DFS investigation

## Debug
- BOARD SIZE
    - board static size by dfs and bfs printing
    - dfs(0, 0, 48, 96)
    - print()
- DFS investigation
    - experiments reveal that there is bug in dfs when n is odd(i.e. by knight's tour study, both n and m is odd, no way to go through whole graph without backtracking)
    - https://www.geeksforgeeks.org/iterative-deepening-searchids-iterative-deepening-depth-first-searchiddfs/
