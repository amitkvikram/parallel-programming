all: thread.out	

thread.out: hw1.cpp
	g++ -pthread hw1.cpp -o thread.out

clean
	rm */*.out
	rm *.out