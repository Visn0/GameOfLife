#!/bin/bash
make clean
make clean_res_parallel
make all

for i in {1..4};
do
    set OMP_NUM_THREADS=$i
    export OMP_NUM_THREADS=$i
    for j in {50..1000..50};
    do
        /usr/bin/time -f "$j %U" -o "results/parallel.$i.thread.time" -a ./generator_parallel 500 $j
    done
done
