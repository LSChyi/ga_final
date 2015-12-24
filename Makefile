all: youbikeOp youbikeGa.o chromosome.o fitnessFunction.o
	g++ -o bin/youbikeOp *.o

youbikeOp: main.cpp youbikeGa.o
	g++ -c main.cpp

youbikeGa.o: youbikeGa.h youbikeGa.cpp fitnessFunction.o
	g++ -c youbikeGa.h youbikeGa.cpp 

chromosome.o: chromosome.h chromosome.cpp
	g++ -c chromosome.h chromosome.cpp

fitnessFunction.o: fitnessFunction.h fitnessFunction.cpp
	g++ -c fitnessFunction.h fitnessFunction.cpp

clean:
	rm -f bin/*.o *.o
