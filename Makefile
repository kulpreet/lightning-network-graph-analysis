CXX=g++
RM=rm -f

readgraph: readgraph.cpp
	g++ -lboost_graph readgraph.cpp -o readgraph

clean:
	rm -f readgraph
