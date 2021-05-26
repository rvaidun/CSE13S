#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn7
EXAMPLE=../../../resources/asgn7

checkdif () {
    if [ "$1" ];
    then
        echo "Difference in the $2 test. press enter to continue printing diff"
        read
        echo $1
        echo "Press any enter to continue"
        read
    fi
}
(cd $MYREPO && make clean && make)
for f in $(find $FILES -type f)
do
    echo "Checking difference for $(basename $f)"
    BANHAMMERNV=$(diff <($MYREPO/banhammer < $f) <($EXAMPLE/banhammer < $f))
    if [ "$BANHAMMERNV" ];
    then
        echo "Difference in the ban hammer with no verbose test. press enter to continue printing diff"
        read
    	diff <($MYREPO/banhammer < $f) <($EXAMPLE/banhammer < $f)
        echo "Press enter to continue"
        read
    fi
    BANHAMMERV=$(diff <($MYREPO/banhammer -s < $f) <($EXAMPLE/banhammer -s < $f))
    if [ "$BANHAMMERV" ];
    then
        echo "Difference in the ban hammer with statistics test. press enter to continue printing diff"
        read
    	diff <($MYREPO/banhammer -s < $f) <($EXAMPLE/banhammer -s < $f)
        echo "Press enter to continue"
        read
    fi
done
echo "-------------------------------------------------"
echo "If there is no diffs, then you are fine for diffs"
echo "Press enter to start valgrind teset"
echo "-------------------------------------------------"
read
valgrind $MYREPO/banhammer < $FILES/calgary/news
echo "-----------------------------------------------"
echo "If there are no memory leaks, then you are fine"
echo "-----------------------------------------------"
(cd $MYREPO && make clean)
