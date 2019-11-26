#!/bin/bash
make clean
make clean_res_parallel
make clean_res_seq
make all

M_patterns=500
N_size=100

for n in {1..4};
do
    export OMP_NUM_THREADS=$n
    for j in {50..1000..50};
    do
        /usr/bin/time -f "$j %e" -o "results/parallel.$n.thread.time" -a ./generator_parallel $N_size $j
    done
done

for j in {50..1000..50};
do
    /usr/bin/time -f "$j %e" -o "results/sequential.time" -a ./generator_sequential $N_size $j
done