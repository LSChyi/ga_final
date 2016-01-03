all: youbikeOp youbikeGa.o chromosome.o fitnessFunction.o
	g++ -std=c++0x -O3 -o bin/youbikeOp *.o

youbikeOp: main.cpp youbikeGa.o
	g++ -std=c++0x -O3 -c main.cpp

youbikeGa.o: youbikeGa.h youbikeGa.cpp fitnessFunction.o
	g++ -std=c++0x -O3 -c youbikeGa.h youbikeGa.cpp 

chromosome.o: chromosome.h chromosome.cpp
	g++ -std=c++0x -O3 -c chromosome.h chromosome.cpp

fitnessFunction.o: fitnessFunction.h fitnessFunction.cpp
	g++ -std=c++0x -O3 -c fitnessFunction.h fitnessFunction.cpp

clean:
	rm -f bin/*.o *.o
	rm -f output/*.csv
	rm -f output/totalCSV/*.csv
