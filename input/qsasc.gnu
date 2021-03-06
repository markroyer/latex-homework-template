set title "Quick Sort of Ascending Data" 
set xlabel "n" 
set xrange [ 0 : 100000 ]
set ylabel "Operations" 
set yrange [ 0 : 5000000000 ]
set terminal pdf enhanced
set output 'qsasc.pdf'
plot "quickSort-asc.data" with lines ti "asc", x*log(x)/log(2) ti "n\log(n)", x*x ti "n^2"