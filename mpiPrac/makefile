all: trapezoidalSerial trapezoidalParallel

trapezoidalSerial: trapezoidalRuleSerial.out 

trapezoidalRuleSerial.out: trapezoidalRuleSerial.cpp
	g++ trapezoidalRuleSerial.cpp -o trapezoidalRuleSerial.out

trapezoidalParallel: trapezoidalRuleParallel.out

trapezoidalRuleParallel.out: trapezoidalRuleParallel.cpp
	mpic++ trapezoidalRuleParallel.cpp -o trapezoidalRuleParallel.out

runSerial: trapezoidalRuleSerial.out
	./trapezoidalRuleSerial.out $(a) $(b) $(n)

runParallel: trapezoidalRuleParallel.out
	mpiexec -n $(nProc) ./trapezoidalRuleParallel.out $(a) $(b) $(n)

clean: 
	rm -f *.out