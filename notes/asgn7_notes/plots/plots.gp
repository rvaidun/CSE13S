set terminal jpeg

set title "Hash Table Size vs Average Seek Length"
set xlabel "Hash Table Size"
set ylabel "Average Seek Length"

set output "news_random_ht.jpg"
plot 'news_hashtable' using 1:3 title 'news' with lines lw 3, \
'random.txt_hashtable' using 1:3 title 'random.txt' with lines lw 3

set output "bible_ht.jpg"
plot 'bible.txt_hashtable' using 1:3 title 'bible.txt' with lines lw 3

set title "Bloom Filter Size vs Average Seek Length"
set xlabel "Bloom Filter Size"

set output "bible_bf_seeklen.jpg"
plot 'bible.txt_bloom' using 1:3 title 'bible.txt' with lines lw 3

set output "new_bf_seeklen.jpg"
plot 'news_bloom' using 1:3 title 'bible.txt' with lines lw 3

set title "Bloom Filter Size vs Total Seeks"
set ylabel "Number of Seeks"

set output "bible_bf_seeks.jpg"
plot 'bible.txt_bloom' using 1:2 title 'bible.txt' with lines lw 3

