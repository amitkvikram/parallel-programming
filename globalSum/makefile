all: arraySum.out threadStartUpOverhead.out busyWait.out sumUsingMutex.out busyWait1.out sumUsingMutex1.out

arraySum.out: arraySum.cpp
	g++ -pthread arraySum.cpp -o arraySum.out

threadStartUpOverhead.out: threadStartUpOverhead.cpp
	g++ -pthread threadStartUpOverhead.cpp -o threadStartUpOverhead.out

busyWait.out: busyWait.cpp
	g++ -pthread busyWait.cpp -o busyWait.out

sumUsingMutex.out: sumUsingMutex.cpp
	g++ -pthread sumUsingMutex.cpp -o sumUsingMutex.out

busyWait1.out: busyWait1.cpp
	g++ -pthread busyWait1.cpp -o busyWait1.out

sumUsingMutex1.out: sumUsingMutex1.cpp
	g++ -pthread sumUsingMutex1.cpp -o sumUsingMutex1.out

clean :
	rm -f *.out 
