#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn5

(cd $MYREPO && make)
rm encode_entropy.txt encode_err_entropy.txt
for f in $(find $FILES -type f)
do
	echo "$(basename $f)" | tr -d '\n' >> encode_entropy.txt
	echo " " | tr -d '\n' >> encode_entropy.txt
	$MYREPO/entropy < $f | tr -d '\n' >> encode_entropy.txt
	echo " " | tr -d '\n' >> encode_entropy.txt
	$MYREPO/encode < $f | $MYREPO/entropy >> encode_entropy.txt

done
for f in $FILES/artificial/*
do
	fn=$(echo "$(basename $f)")
	echo $fn
	rm $fn.entrop_err.txt
for x in {1..100}
do
	y=$(echo $x | awk '{printf "%f",$1 / 100}')
	e=$($MYREPO/encode < $f | $MYREPO/error -e $y | $MYREPO/entropy)
       	echo "$y $e" | awk '{print $1,$2}' >> "$fn.entrop_err.txt"
done
#$MYREPO/encode < $FILES/large/bible.txt | $MYREPO/error -e $y | $MYREPO/entropy >> encode_err_entropy.txt
done
(cd $MYREPO && make clean)
