all: thread.out	

thread.out: temp.cpp
	g++ -pthread temp.cpp -o temp.out

clean : *.out 
	rm */*.out
	rm *.out