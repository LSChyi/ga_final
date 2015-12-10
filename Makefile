all: youbikeOp
	g++ -o bin/youbike_op *.o

youbikeOp: main.cpp youbikeGa.o
	g++ -c main.cpp

youbikeGa.o: youbikeGa.h youbikeGa.cpp
	g++ -c youbikeGa.h youbikeGa.cpp 

clean:
	rm -f bin/*.o *.o