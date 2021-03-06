LDFLAGS=-L/usr/local/lib
CXXFLAGS=-std=c++11

RM=rm -f

all: run build_test

readgraph.o: src/readgraph.cpp src/include/readgraph.hpp
	$(CXX) $(CXXFLAGS) -c src/readgraph.cpp

run.o: src/readgraph.cpp src/include/readgraph.hpp src/readgraph.cpp src/run.cpp src/include/algos.hpp
	$(CXX) $(CXXFLAGS) -c src/run.cpp

run: run.o readgraph.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o readgraph run.o readgraph.o -lboost_graph -lboost_program_options -lboost_system -lboost_filesystem

readgraph_test.o: src/readgraph.cpp src/include/readgraph.hpp src/readgraph_test.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c src/readgraph_test.cpp

build_test: readgraph.o readgraph_test.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test_readgraph readgraph_test.o readgraph.o -lboost_graph -lboost_unit_test_framework -lboost_program_options

test: build_test
	./test_readgraph

clean:
	rm -f readgraph test_readgraph run *.o
