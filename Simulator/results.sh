#!/bin/bash

cd ../Generator
make clean
make all
./generator_parallel 50 1000
cd ../Simulator
make clean
make clean_res_parallel
make clean_res_seq
make all

generations=50

for i in {1..4};
do
    set OMP_NUM_THREADS=$i
    export OMP_NUM_THREADS=$i
    for j in {50..1000..50};
    do
        /usr/bin/time -f "$j %U" -o "results/parallel.$i.thread.time" -a ./gameoflife_parallel ../Generator/patterns/ $generations $j
    done
done

for j in {50..1000..50};
do
    /usr/bin/time -f "$j %U" -o "results/sequential.time" -a ./gameoflife_sequential ../Generator/patterns/ $generations $j        
done
