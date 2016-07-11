set title "Quick Sort of Random Data" 
set xlabel "n" 
set xrange [ 0 : 100000 ]
set ylabel "Operations" 
set yrange [ 0 : 2520000 ]
set terminal pdf enhanced
set output 'qsrandom.pdf'
plot "quickSort-random.data" with lines ti "random", x*log(x)/log(2) ti "n\log(n)", x*x ti "n^2"