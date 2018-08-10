CXX=g++
RM=rm -f

readgraph:
	g++ -lboost_graph readgraph.cpp -o readgraph

clean:
	rm -f readgraph
