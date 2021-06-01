#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn7
EXAMPLE=../../../resources/asgn7

checkdif () {
    DIFFF=$(diff <($2 < $1) <($3 < $1))
    if [ "$DIFFF" ];
    then
        echo "Difference in the $4 test. press enter to continue printing diff"
        read
        diff <($2 < $1) <($3 < $1)
        echo "Press any enter to continue"
        read
    fi
}
(cd $MYREPO && make clean && make)
for f in $(find $FILES -type f)
do
    echo "Checking difference for $(basename $f)"
    checkdif $f "$MYREPO/banhammer" "$EXAMPLE/banhammer" "normal"
    checkdif $f "$MYREPO/banhammer -m" "$EXAMPLE/banhammer -m" "move to front"
    checkdif $f "$MYREPO/banhammer -s" "$EXAMPLE/banhammer -s" "statistics"
    checkdif $f "$MYREPO/banhammer -s -m" "$EXAMPLE/banhammer -s -m" "statistics move to front"
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
