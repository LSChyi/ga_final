all: youbikeOp youbikeGa.o chromosome.o fitnessFunction.o
	g++ -std=c++0x -o bin/youbikeOp *.o

youbikeOp: main.cpp youbikeGa.o
	g++ -std=c++0x -c main.cpp

youbikeGa.o: youbikeGa.h youbikeGa.cpp fitnessFunction.o
	g++ -std=c++0x -c youbikeGa.h youbikeGa.cpp 

chromosome.o: chromosome.h chromosome.cpp
	g++ -std=c++0x -c chromosome.h chromosome.cpp

fitnessFunction.o: fitnessFunction.h fitnessFunction.cpp
	g++ -std=c++0x -c fitnessFunction.h fitnessFunction.cpp

clean:
	rm -f bin/*.o *.o
	rm -f output/*.csv
	rm -f output/totalCSV/*.csv
