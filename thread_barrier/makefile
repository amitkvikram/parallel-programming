all: barrier1.out barrier2.out

barrier1.out: threadBarrier1.cpp
	g++ -pthread threadBarrier1.cpp -o barrier1.out

barrier2.out: threadBarrier2.cpp
	g++ -pthread threadBarrier2.cpp -o barrier2.out

clean: *.out
	rm *.out