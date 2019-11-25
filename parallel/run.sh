#!/bin/bash
for i in {1..4};
do
    set OMP_NUM_THREADS=$i
    export OMP_NUM_THREADS=$i
    for j in {50..1000..50};
    do
        /usr/bin/time -f "$j %U" -o "parallel.$i.thread.time" -a ./generator $j 500
    done
done
