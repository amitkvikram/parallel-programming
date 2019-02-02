all: a.out messagePassQueue.out

a.out: messagePassing.cpp
	g++ -pthread messagePassing.cpp -o a.out

messagePassQueue.out: messagePassQueue.cpp
	g++ -pthread messagePassQueue.cpp -o messagePassQueue.out

clean: *.out
	rm *.out