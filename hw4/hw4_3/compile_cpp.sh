#!/bin/bash

problem=ada-hw4-p3
problem2=test
g++ -O2 -std=c++17 grader.cpp $problem.cpp -o $problem
#g++ -O2 -std=c++17 grader.cpp $problem2.cpp -o $problem2
