LDFLAGS=-L/usr/local/lib
CXXFLAGS=-std=c++11

RM=rm -f

all: run build_test

readgraph.o: src/readgraph.cpp src/readgraph.hpp
	$(CXX) $(CXXFLAGS) -c src/readgraph.cpp 

run.o: src/readgraph.cpp src/readgraph.hpp src/readgraph.cpp src/run.cpp src/algos.hpp
	$(CXX) $(CXXFLAGS) -c src/run.cpp

run: run.o readgraph.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o readgraph run.o readgraph.o -lboost_graph

readgraph_test.o: src/readgraph.cpp src/readgraph.hpp src/readgraph_test.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c src/readgraph_test.cpp

build_test: readgraph.o readgraph_test.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test_readgraph readgraph_test.o readgraph.o -lboost_graph -lboost_unit_test_framework

test: build_test
	./test_readgraph

clean:
	rm -f readgraph test_readgraph run *.o
