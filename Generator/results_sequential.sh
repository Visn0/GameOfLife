#!/bin/bash

make clean
make all

for j in {50..2000..50};
do
    /usr/bin/time -f "$j %U" -o "results/sequential.time" -a ./generator_sequential 50 $j
done