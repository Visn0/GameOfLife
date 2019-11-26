set xlabel 'M (patterns)'
set ylabel 'time(ms)'
set term png
set output 'images/execution_time.graph'
plot 'results/parallel.2.thread.time' using  1:2 with lines title '2 threads', \
'results/parallel.3.thread.time' using  1:2 with lines title '3 threads', \
'results/parallel.4.thread.time' using  1:2 with lines title '4 threads', \
'results/sequential.time' using  1:2 with lines title 'Sequential'

set xlabel 'M (patterns)'
set ylabel 'speedup (sequential / parallel)'
set term png
set output 'images/speedup.graph'
plot 'results/speedup_efficiency.2.thread' using  1:2 with lines title '2 threads', \
'results/speedup_efficiency.3.thread' using  1:2 with lines title '3 threads', \
'results/speedup_efficiency.4.thread' using  1:2 with lines title '4 threads'

set xlabel 'M (patterns)'
set ylabel 'efficiency (speedup / threads)'
set term png
set output 'images/efficiency.graph'
plot 'results/speedup_efficiency.2.thread' using  1:3 with lines title '2 threads', \
'results/speedup_efficiency.3.thread' using  1:3 with lines title '3 threads', \
'results/speedup_efficiency.4.thread' using  1:3 with lines title '4 threads'