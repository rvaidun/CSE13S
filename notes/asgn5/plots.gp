set terminal jpeg
set yrange [0:14]
set xlabel "Error Rate"

set output "error_entropy.jpg"
set title "Error rate vs Entropy"
set ylabel "Entropy"
plot 'aaa.txt.entrop_err.txt' using 1:2 title 'aaa.txt' with lines lw 3, \
'random.txt.entrop_err.txt' using 1:2 title 'random.txt' with lines lw 3, \
'alphabet.txt.entrop_err.txt' using 1:2 title 'alphabet.txt' with lines lw 3
