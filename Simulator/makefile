all:
	g++ -o gameoflife_parallel gameoflife_parallel.cpp -fopenmp
	g++ -o gameoflife_sequential gameoflife_sequential.cpp

parallel: gameoflife_parallel.cpp
	g++ -o gameoflife_parallel gameoflife_parallel.cpp -fopenmp

sequential: gameoflife_sequential.cpp
	g++ -o gameoflife_sequential gameoflife_sequential.cpp

clean:
	rm gameoflife_parallel
	rm gameoflife_sequential
	rm reports/*