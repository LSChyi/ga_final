all: youbike_op
	g++ -o bin/youbike_op bin/*.o

youbike_op: main.cpp
	g++ -c main.cpp -o bin/youbike_op.o

clean:
	rm -f bin/*.o