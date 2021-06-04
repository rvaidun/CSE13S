set terminal jpeg

set title "Hash Table Size vs Average Seek Length"
set xlabel "Hash Table Size"
set ylabel "Average Seek Length"

set output "news_ht.jpg"
plot 'news_hashtable' using 1:3 title 'news' with lines lw 3, \
'news_hashtable_mtf' using 1:3 title 'news - MTF' with lines lw 3

set output "bible_ht.jpg"
plot 'bible.txt_hashtable' using 1:3 title 'bible.txt' with lines lw 3, \

set output "bible_ht_mtf.jpg"
plot 'bible.txt_hashtable_mtf' using 1:3 title 'bible.txt - MTF' with lines lw 3

set title "Bloom Filter Size vs Average Seek Length"
set xlabel "Bloom Filter Size"

set output "news_bf_seeklen.jpg"
plot 'news_bloom' using 1:3 title 'news' with lines lw 3, \
'news_bloom_mtf' using 1:3 title 'news - MTF' with lines lw 3


set title "Bloom Filter Size vs Total Seeks"
set ylabel "Number of Seeks"

set output "news_bf_seeks.jpg"
plot 'news_bloom' using 1:2 title 'news' with lines lw 3
