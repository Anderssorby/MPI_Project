#!/bin/bash

echo "Strating processes"
qsub "go1-4.sh"
qsub "go1-16.sh"
qsub "go1-36.sh"
qsub "go2-32.sh"
qsub "go8-36.sh"

rbstat
