test: test.o FPTree.o json.o
	g++ -std=c++11 test.o FPTree.o json.o -o test

test.o: test.cpp
	g++ -std=c++11 -c test.cpp -o test.o

FPTree.o: FPTree.h FPTree.cpp
	g++ -std=c++11 -c FPTree.cpp -o FPTree.o

json.o:	json.h json.cpp
	g++ -std=c++11 -c json.cpp -o json.o
clean:
	rm test.o FPTree.o json.o sample.json
