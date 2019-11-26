#!/bin/bash
make clean
make clean_res_parallel
make clean_res_seq
make all

M_patterns=500

for n in {1..4};
do
    set OMP_NUM_THREADS=$n
    export OMP_NUM_THREADS=$n
    for n in {500..550..10};
    do
        /usr/bin/time -f "$n %U" -o "times.out" -a ./generator_parallel $n $M_patterns
    done
done

for j in {50..1000..50};
do
    /usr/bin/time -f "$j %U" -o "results/sequential.time" -a ./generator_sequential $j $M_patterns
done