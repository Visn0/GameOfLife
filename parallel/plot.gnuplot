set xlabel 'n (pattern size)'
set ylabel 'speedup (sequential / parallel)'
set term png
set output 'images/efficency.graph'
plot 'speedup.2.thread' using  1:(($2 / ($3 / 2))/ 2) with lines title '2 threads', \
'speedup.3.thread' using  1:(($2 / ($3 / 3))/ 3) with lines title '3 threads', \
'speedup.4.thread' using  1:(($2 / ($3 / 4))/ 4) with lines title '4 threads', \