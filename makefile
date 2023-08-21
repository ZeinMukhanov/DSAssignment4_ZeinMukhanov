target: main.o flighthashtable.o
	g++ main.o flighthashtable.o -o main
flighthashtable.o: flighthashtable.cpp flighthashtable.h flightticket.h mylist.h
	g++ -c flighthashtable.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -r *.o