#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn6
EXAMPLE=../../../resources/asgn6
BIBLE=../../../resources/corpora/large/bible.txt
(cd $MYREPO && make clean && make)
for f in $(find $FILES -type f)
do
    echo "Checking difference for $(basename $f)"
    ENCODEVERBOSE=$(diff <($MYREPO/encode -v < $f 2>&1) <($EXAMPLE/encode -v < $f 2>&1))
    if ["$ENCODEVERBOSE"];
    then
        echo "Difference in the encode verbose press any key to continue"
        read
        echo $ENCODEVERBOSE
        echo "Press any key to continue"
        read
    fi
    DECODEVERBOSE=$(diff <($MYREPO/encode < $f | $MYREPO/decode -v 2>&1) <($EXAMPLE/encode < $f | $EXAMPLE/decode -v 2>&1))
    if ["$DECODEVERBOSE"];
    then
        echo "Difference in the decode verbose press any key to continue"
        read
        echo $DECODEVERBOSE
        echo "Press any key to continue"
        read
    fi
    ENCODEDECODE=$(diff <($MYREPO/encode < $f | $MYREPO/decode) $f)
    if ["$ENCODEDECODE"];
    then
        echo "Difference in the encode decode press any key to continue"
        read
        echo $ENCODEDECODE
        echo "Press any key to continue"
        read
    fi
    ENCODEDECODEPIPE=$(cat $f | $MYREPO/encode | $MYREPO/decode | diff - $f)
    if ["$ENCODEDECODE"];
    then
        echo "Difference in the encode decode press any key to continue"
        read
        echo $ENCODEDECODE
        echo "Press any key to continue"
        read
    fi
done
valgrind ./$MYREPO/encode -o bible.encode < $BIBLE
read
valgrind ./$MYREPO/decode -o bible.decode < bible.encode
rm bible.decode bible.encode
(cd $MYREPO && make clean)
(cd $EXAMPLE && git clean -f)
