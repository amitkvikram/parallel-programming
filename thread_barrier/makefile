all: threadBarrier1.out threadBarrier2.out threadBarrier3.out threadBarrier4.out

threadBarrier1.out: threadBarrier1.cpp
	g++ -pthread threadBarrier1.cpp -o threadBarrier1.out

threadBarrier2.out: threadBarrier2.cpp
	g++ -pthread threadBarrier2.cpp -o threadBarrier2.out

threadBarrier3.out: threadBarrier3.cpp
	g++ -pthread threadBarrier3.cpp -o threadBarrier3.out

threadBarrier4.out: threadBarrier4.cpp
	g++ -pthread threadBarrier4.cpp -o threadBarrier4.out

clean: 
	rm -f *.out