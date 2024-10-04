#!/bin/bash

g++ -I ../../headers/ -g -o test_program ../../src/*.cpp ./test_gcc.cpp -Wall -Wextra 2> ./stderr.txt
