#!/bin/bash

cd ../Generator
make clean 
make all
./generator_parallel 50 1000
cd ../Simulator
make clean
make all

for j in {50..1000..50};
do
    /usr/bin/time -f "$j %U" -o "results/sequential.time" -a ./gameoflife_sequential ../Generator/patterns/ 10 $j        
done