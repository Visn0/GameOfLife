all:
	g++ generator_parallel.c -o generator_parallel -fopenmp
	g++ generator_sequential.c -o generator_sequential

parallel:
	g++ generator_parallel.c -o generator_parallel -fopenmp

sequential:
	g++ generator_sequential.c -o generator_sequential

clean:
	rm generator_parallel
	rm generator_sequential		
	rm reports/*		
	rm patterns/*.txt	

clean_res_parallel:
	rm results/parallel*

clean_res_seq:
	rm results/sequential*
