#!/bin/bash
(cd ../../asgn3 && make)
mkdir plots
newline=$'\n'
for i in bubble shell quick_stack Quick_queue
do
echo $i
echo ${i:0:1}
var=""
var2=""
pat='[0-9]+ '
for ((j=100; j <=1000; j+= 1))
do
OUTPUT=$(../../asgn3/sorting -${i:0:1 } -n $j -p 0| tail -n +2)
OUTPUT2=$(../../asgn3/sorting -${i:0:1 } -r $j -p 0 -n 1000| tail -n +2)

NUMS=$(echo $OUTPUT | tr -d [a-z][A-Z],:)
NUMS2=$(echo $OUTPUT2 | tr -d [a-z][A-Z],:)
printf -v var '%s\n%s' "$var" "$NUMS"
printf -v var2 '%s\n%s' "$var2" "$NUMS2"
echo "$var"
echo "$var2"
done
echo "$var" > plots/$i.txt
echo "$var2" > plots/$i.average.txt
done

cd plots
gnuplot plots.gp
cd ..
(cd ../../asgn3 && make clean)
