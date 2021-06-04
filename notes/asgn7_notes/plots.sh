FILES=../../../resources/corpora
MYREPO=../../asgn7
(cd $MYREPO && make)

# for f in $(find $FILES/artificial -type f)
for f in $FILES/large/bible.txt
do
    echo "came in"
    echo > plots/$(basename $f)_hashtable_mtf
    echo > plots/$(basename $f)_bloom_mtf
    for ((t = 500 ; t <= 20000 ; t+=500))
    do
        echo $t $($MYREPO/banhammer -m -s -t $t < $f) | awk '{gsub(/[^0-9. ]/,"")}1' >> plots/$(basename $f)_hashtable_mtf
    done

    for ((ff = 256 ; ff <= 33554432 ; ff = ff*3/2))
    do
        ffint=${ff%.*}
        echo $ffint
        echo $ff $($MYREPO/banhammer -m -s -f $ffint < $f) | awk '{gsub(/[^0-9. ]/,"")}1' >> plots/$(basename $f)_bloom_mtf
    done
done
            

