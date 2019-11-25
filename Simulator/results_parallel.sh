#!/bin/bash

cd ../Generator
make clean 
make all
./generator_parallel 50 1000
cd ../Simulator
make clean
make all

for i in {1..4};
do
    set OMP_NUM_THREADS=$i
    export OMP_NUM_THREADS=$i
    for j in {50..1000..50};
    do
        /usr/bin/time -f "$j %U" -o "results/parallel.$i.thread.time" -a ./gameoflife_parallel ../Generator/patterns/ 10 $j
    done
done
