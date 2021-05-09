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
$MYREPO/entropy < $FILES/large/bible.txt >> encode_err_entropy.txt
for x in {1..5}
do
	y=`bc <<< "scale=2; $x/100"`
$MYREPO/encode < $FILES/large/bible.txt | $MYREPO/error -e $y | $MYREPO/entropy >> encode_err_entropy.txt
done
(cd $MYREPO && make clean)
