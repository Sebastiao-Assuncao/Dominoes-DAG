#!/bin/bash

g++ -O3 -Wall -o randomDAG randomDAG.cpp -lm
g++ -std=c++11 -O3 -Wall P1.cpp -lm

for i in {0..20}; do

    N=$(( 50000*i ))
    p=0.4
    echo $N
    ./randomDAG ${i} ${p} [seed] > test.txt
    ./a.out < "test.txt" >> cena.txt
done
