#!/bin/bash
g++ -std=c++14 -o run src/main.cpp src/encoder.cpp src/decoder.cpp src/binarytree.cpp src/huffmancoding.cpp && ./run && rm run
