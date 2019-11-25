set xlabel 'n (pattern size)'
set ylabel 'speedup (sequential / parallel)'
set term png
set output 'images/efficency.graph'
plot 'results/speedup.2.thread' using  1:(($2 / ($3 / 2))/ 2) with lines title '2 threads', \
'results/speedup.3.thread' using  1:(($2 / ($3 / 3))/ 3) with lines title '3 threads', \
'results/speedup.4.thread' using  1:(($2 / ($3 / 4))/ 4) with lines title '4 threads', \