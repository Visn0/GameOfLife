#!/bin/bash

make clean
make clean_res_seq
make all

for j in {50..1000..50};
do
    /usr/bin/time -f "$j %U" -o "results/sequential.time" -a ./generator_sequential 500 $j
done