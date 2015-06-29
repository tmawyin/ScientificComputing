#!/bin/bash
## Script to compile and run HW1 C++ code for SCMP122
## C++ code calculates the hyperbolic tangent from the range [-2,2]

## Compiling code:
## -o -> generates object file to run called HW1_TMawyin
## -Wall -> prints warnings if any
## -O2 -> optimization flag
g++ HW1_TMawyin.cpp -o HW1_TMawyin -Wall -O2

## Running the code: Prints output to screen and generates file "Results.txt"
./HW1_TMawyin
