#!/bin/bash
(cd ../../asgn2 && make)
mkdir plots
for i in asin acos atan log
do
if [ ${i:0:1} == "a" ]
then ../../asgn2/mathlib-test -${i:1:1} > plots/$i.txt
else
../../asgn2/mathlib-test -${i:0:1} > plots/$i.txt
fi
done
cd plots
gnuplot <<XX
set terminal jpeg
set output "arcsin.jpg"
plot 'asin.txt' using 1:4 title 'arcsin' with linespoints
set output "arccos.jpg"
plot 'acos.txt' using 1:4 title 'arccos' with linespoints
set output "arctan.jpg"
plot 'atan.txt' using 1:4 title 'arctan' with linespoints
set output "log.jpg"
plot 'log.txt' using 1:4 title 'log' with linespoints
XX
cd ..
(cd ../../asgn2 && make clean)
