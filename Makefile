all: youbikeOp youbikeGa.o chromosome.o
	g++ -o bin/youbikeOp *.o

youbikeOp: main.cpp youbikeGa.o
	g++ -c main.cpp

youbikeGa.o: youbikeGa.h youbikeGa.cpp
	g++ -c youbikeGa.h youbikeGa.cpp 

chromosome.o: chromosome.h chromosome.cpp
	g++ -c chromosome.h chromosome.cpp

clean:
	rm -f bin/*.o *.o