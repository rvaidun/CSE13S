#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn5
EXAMPLE=../../../resources/asgn5

(cd $MYREPO && make)
(cd $EXAMPLE && clang -o error error.c && clang -o entropy entropy.c -lm)
rm encode_entropy.txt
for f in $(find $FILES -type f)
do
	echo "$(basename $f)" | tr -d '\n' >> encode_entropy.txt
	echo " " | tr -d '\n' >> encode_entropy.txt
	$MYREPO/entropy < $f | tr -d '\n' >> encode_entropy.txt 
	echo " " | tr -d '\n' >> encode_entropy.txt
	$MYREPO/encode < $f | $MYREPO/entropy >> encode_entropy.txt
	#diff <($MYREPO/encode < $f | $MYREPO/error -e 0.01 | $MYREPO/decode -v 2>&1) <($EXAMPLE/encode < $f | $EXAMPLE/error -e 0.01 | $EXAMPLE/decode -v 2>&1)
done
(cd $MYREPO && make clean)
(cd $EXAMPLE && git clean -f)
