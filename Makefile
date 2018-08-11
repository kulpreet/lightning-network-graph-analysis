CXX=g++
RM=rm -f

all: run build_test

readgraph.o: src/readgraph.cpp src/readgraph.hpp
	$(CXX) -c src/readgraph.cpp 

run.o: src/readgraph.cpp src/readgraph.hpp src/run.cpp src/algos.hpp
	$(CXX) -c src/run.cpp

run: run.o readgraph.o
	$(CXX) -lboost_graph -o readgraph run.o readgraph.o

readgraph_test.o: src/readgraph.cpp src/readgraph.hpp src/readgraph_test.cpp
	$(CXX) -c src/readgraph_test.cpp

build_test: readgraph.o readgraph_test.o
	$(CXX) -lboost_graph -lboost_unit_test_framework -o test_readgraph readgraph.o readgraph_test.o

test: build_test
	./test_readgraph

clean:
	rm -f readgraph test_readgraph run *.o
