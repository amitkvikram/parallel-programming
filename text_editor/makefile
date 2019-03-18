all: kilo kiloSerial

runParallel: kilo
	./kilo $(filename)

runSerial: kiloSerial
	./kiloSerial $(filename)

kilo: kilo.cpp typeDefinition.h
	g++ -pthread kilo.cpp -o kilo

kiloSerial: kiloSerial.cpp typeDefinition.h
	g++ -pthread kiloSerial.cpp -o kiloSerial