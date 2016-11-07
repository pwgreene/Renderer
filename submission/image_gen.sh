#!/bin/bash

read -p "How many files? >" nfiles
read -p "Source dir >" srcdir
read -p "Target dir >" dstdir
BIN=../build/a4
SIZE="800 800"

for i in `seq 0 $nfiles`
do
    ${BIN} -size ${SIZE} -input "$srcdir/scene$i.txt" -output "$dstdir/scene$i.png" -bounces 4
done