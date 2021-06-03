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
        echo "$DIFFF"
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
for i in {1..5}
do
    NUM1=$RANDOM
    NUM2=$RANDOM
    echo "Checking difference with hash table size of $NUM1 and bloom filter size of $NUM2"
    checkdif "$FILES/calgary/news" "$MYREPO/banhammer -s -t $NUM1 -f $NUM2" "$EXAMPLE/banhammer -s -t $NUM1 -f $NUM2" "statistics"
    checkdif "$FILES/calgary/news" "$MYREPO/banhammer -s -m -t $NUM1 -f $NUM2" "$EXAMPLE/banhammer -s -m -t $NUM1 -f $NUM2" "statistics move to front"
done
echo "-------------------------------------------------"
echo "If there is no diffs, then you are fine for diffs"
echo "Press enter to start valgrind tests"
echo "-------------------------------------------------"
read
VALGRINDMESSAGE=$(valgrind --error-exitcode=1 --leak-check=full --log-fd=9 $MYREPO/banhammer < $FILES/calgary/news 9>&1 1>/dev/null 2>/dev/null)
VALGRINDSTATUS=$?
if [ $VALGRINDSTATUS -ne 0 ];then
        echo "$VALGRINDMESSAGE"    
else
        echo "No memory leaks found"
fi
echo "-----------------------------------------------"
echo "If there are no memory leaks, then you are fine"
echo "Press enter to start scan build"
echo "-----------------------------------------------"
SCANBUILDMESSAGE=$(cd $MYREPO && scan-build make 2>&1)
SCANBUILDSTATUS=$?
if [ SCANBUILDSTATUS != 0 ];then
        echo "$SCANBUILDMESSAGE"
else
    echo "No problems with scan build"    
fi
(cd $MYREPO && make clean)
