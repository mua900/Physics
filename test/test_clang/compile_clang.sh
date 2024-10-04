#!/bin/bash

clang++-18 -I ../../headers/ -g -Wall -Wextra ../../src/*.cpp ./testclang.cpp 2> ./stderr.txt
