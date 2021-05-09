#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn5
EXAMPLE=../../../resources/asgn5
(cd $MYREPO && make)
(cd $EXAMPLE && clang -o error error.c && clang -o entropy entropy.c -lm)
#diff <($MYREPO/encode < $FILES/artificial/a.txt | $MYREPO/error -e 0.01 | $MYREPO/decode -v | diff - $FILES/artificial/a.txt) <($EXAMPLE/encode < $FILES/artificial/a.txt | $EXAMPLE/error -e 0.01 | $EXAMPLE/decode -v | diff - $FILES/artificial/a.txt)
for f in $(find $FILES -type f)
do
	echo "Checking difference for $(basename $f)"
	diff <($MYREPO/encode < $f | $MYREPO/error -e 0.01 | $MYREPO/decode -v 2>&1) <($EXAMPLE/encode < $f | $EXAMPLE/error -e 0.01 | $EXAMPLE/decode -v 2>&1)
done
(cd $MYREPO && make clean)
(cd $EXAMPLE && git clean -f)
