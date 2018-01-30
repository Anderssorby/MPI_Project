#!/bin/bash

mpicc -O3 -xCORE-AVX2 -align $@ || exit
echo "Strating processes"

qsub go.sh

rbstat
