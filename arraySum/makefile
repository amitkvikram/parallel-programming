all: arraySum.out run

arraySum.out: arraySum.cpp
	g++ -pthread arraySum.cpp -o arraySum.out

run: threadStartUpOverhead.cpp
	g++ -pthread threadStartUpOverhead.cpp -o threadStartUpOverhead.out

busyWait: busyWait.cpp
	g++ -pthread busyWait.cpp -o busyWait.out

clean : *.out
	rm *.out 