#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn6
EXAMPLE=../../../resources/asgn6
BIBLE=../../../resources/corpora/large/bible.txt

checkdif () {
    if [ "$1" ];
    then
        echo "Difference in the $2 press enter to continue printing diff"
        read
        echo $1
        echo "Press any enter to continue"
        read
    fi
}
(cd $MYREPO && make)
for f in $(find $FILES -type f)
do
    echo "Checking difference for $(basename $f)"

    ENCODEVERBOSE=$(diff <($MYREPO/encode -v < $f 2>&1) <($EXAMPLE/encode -v < $f 2>&1))
    checkdif $ENCODEVERBOSE "encoded verbose file"

    DECODEVERBOSE=$(diff <($MYREPO/encode < $f | $MYREPO/decode -v 2>&1) <($EXAMPLE/encode < $f | $EXAMPLE/decode -v 2>&1))
    checkdif $DECODEVERBOSE "decoded verbose file"

    ENCODEDECODE=$(diff <($MYREPO/encode < $f | $MYREPO/decode) $f)
    checkdif $ENCODEDECODE "encode to decode"

    ENCODEDECODEPIPE=$(cat $f | $MYREPO/encode | $MYREPO/decode | diff - $f)
    checkdif $ENCODEDECODE "encode to decode with pipe"
done
echo "-----------------------------------------------"
echo "If there is no diffs, then you are fine"
echo "Press enter to start valgrind check for encode"
echo "-----------------------------------------------"
read
valgrind ./$MYREPO/encode -o bible.encode < $BIBLE
echo "-----------------------------------------------"
echo "If there are no memory leaks, then you are fine"
echo "Press enter to start valgrind check for decode"
echo "-----------------------------------------------"
read
valgrind ./$MYREPO/decode -o bible.decode < bible.encode
echo "-----------------------------------------------"
echo "If there are no memory leaks, then you are fine"
echo "-----------------------------------------------"
rm bible.decode bible.encode
(cd $MYREPO && make clean)
