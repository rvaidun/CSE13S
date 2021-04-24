set terminal jpeg
set style line 1 lw 3
set output "all_comparisons.jpg"
set title "All Comparisons"
set yrange [0:100000]
plot 'shell.txt' using 1:3 title 'Shell Sort' with lines lw 3, \
'bubble.txt' using 1:3 title 'Bubble Sort' with lines lw 3, \
'Quick_queue.txt' using 1:3 title 'Quick Sort (Queue)' with lines lw 3, \
'quick_stack.txt' using 1:3 title 'Quick Sort (Stack)' with lines lw 3
set output "all_moves.jpg"
set title "All Moves"
set yrange [0:100000]
plot 'shell.txt' using 1:2 title 'Shell Sort' with lines lw 3, \
'bubble.txt' using 1:2 title 'Bubble Sort' with lines lw 3, \
'Quick_queue.txt' using 1:2 title 'Quick Sort (Queue)' with lines lw 3, \
'quick_stack.txt' using 1:2 title 'Quick Sort (Stack)' with lines lw 3

set yrange [*:*]
set output "quick_moves.jpg"
set title "Quick Moves"
plot 'Quick_queue.txt' using 1:2 title 'Quick Sort (Queue)' with lines lw 3, \
'quick_stack.txt' using 1:2 title 'Quick Sort (Stack)' with lines lw 3, \

set output "quick_max_sizes.jpg"
set title "Max Queue/Stack Size"
plot 'Quick_queue.txt' using 1:4 title 'Quick Sort (Queue)' with lines lw 3, \
'quick_stack.txt' using 1:4 title 'Quick Sort (Stack)' with lines lw 3, \
