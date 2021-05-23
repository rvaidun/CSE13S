#!/bin/bash

FILES=../../../resources/corpora
MYREPO=../../asgn6
EXAMPLE=../../../resources/asgn6
(cd $MYREPO && make clean && make)
for f in $(find $FILES -type f)
do
        echo "Checking difference for $(basename $f)"
        #($MYREPO/encode -v -i $f 2> /tmp/rahulencodeverbose > /dev/null)
        #($EXAMPLE/encode -v -i $f 2> /tmp/profencodeverbose > /dev/null)
        #diff /tmp/rahulencodeverbose /tmp/profencodeverbose
        diff <($MYREPO/encode -v < $f 2>&1) <($MYREPO/encode -v < $f 2>&1)
        diff <($MYREPO/encode < $f | $MYREPO/decode -v 2>&1) <($EXAMPLE/encode < $f | $EXAMPLE/decode -v 2>&1)
        diff <($MYREPO/encode < $f | hd) <($EXAMPLE/encode < $f | hd)
        diff <($MYREPO/encode < $f | $MYREPO/decode) $f
done
(cd $MYREPO && make clean)
(cd $EXAMPLE && git clean -f)
