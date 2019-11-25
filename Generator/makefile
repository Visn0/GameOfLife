all:
	g++ generator_parallel.c -o generator_parallel -fopenmp
	g++ generator_sequential.c -o generator_sequential -fopenmp

parallel:
	g++ generator_parallel.c -o generator_parallel -fopenmp

sequential:
	g++ generator_sequential.c -o generator_sequential -fopenmp

clean:
	rm generator_parallel
	rm generator_sequential		
	rm reports/*
	rm patterns/*

