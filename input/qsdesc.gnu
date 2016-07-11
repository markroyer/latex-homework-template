set title "Quick Sort of Descending Data" 
set xlabel "n" 
set xrange [ 0 : 100000 ]
set ylabel "Operations" 
set yrange [ 0 : 5000000000 ]
set terminal pdf enhanced
set output 'qsdesc.pdf'
plot "quickSort-desc.data" with lines ti "desc", x*log(x)/log(2) ti "n\log(n)", x*x ti "n^2"