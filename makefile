CFLAGS=-std=c++14

optimalPath.x: ClientParser.o Graph.o main.o
	g++ $(CFLAGS) ClientParser.o Graph.o main.o -o optimalPath.x

ClientParser.o: ClientParser.hpp ClientParser.cpp RentalForm.hpp
	g++ $(CFLAGS) ClientParser.cpp -o ClientParser.o -c

Graph.o: Graph.h Graph.cpp RentalForm.hpp
	g++ $(CFLAGS) Graph.cpp -o Graph.o -c

main.o: ClientParser.cpp Graph.cpp RentalForm.hpp FileOutput.hpp
	g++ $(CFLAGS) main.cpp -o main.o -c

clean:
	rm -f *.o *~ *.x