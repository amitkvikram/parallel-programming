all: linkedList1.out linkedList2.out test1 test2

run: linkedList1.out

linkedList1.out: linkedList1.cpp
	g++ -pthread linkedList1.cpp -o linkedList1.out

linkedList2.out: linkedList2.cpp
	g++ -pthread linkedList2.cpp -o linkedList2.out

test1: createTest1.out
	./createTest1.out > test1.txt

createTest1.out: createTest1.cpp
	g++ createTest1.cpp -o createTest1.out

test2: createTest2.out
	./createTest2.out > test2.txt

createTest2.out: createTest2.cpp
	g++ createTest2.cpp -o createTest2.out

allocationOverhead.out: allocationOverhead.cpp
	g++ allocationOverhead.cpp -o allocationOverhead.out
	
clean:
	rm -f *.out
	rm -f *.txt 