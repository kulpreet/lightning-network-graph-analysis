LDFLAGS=-L/usr/local/lib

RM=rm -f

all: run build_test

readgraph.o: src/readgraph.cpp src/readgraph.hpp
	$(CXX) -c src/readgraph.cpp 

run.o: src/readgraph.cpp src/readgraph.hpp src/run.cpp src/algos.hpp
	$(CXX) -c src/run.cpp

run: run.o readgraph.o
	$(CXX) $(LDFLAGS) -o readgraph run.o readgraph.o -lboost_graph

readgraph_test.o: src/readgraph.cpp src/readgraph.hpp src/readgraph_test.cpp
	$(CXX) $(LDFLAGS) -c src/readgraph_test.cpp

build_test: readgraph.o readgraph_test.o
	$(CXX) $(LDFLAGS) -o test_readgraph readgraph_test.o readgraph.o -lboost_graph -lboost_unit_test_framework

test: build_test
	./test_readgraph

clean:
	rm -f readgraph test_readgraph run *.o
