#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_utility.hpp>
#include <iostream>
#include <boost/graph/biconnected_components.hpp>

using namespace boost;
using namespace std;

struct LitVertex {
  string name;
  string last_update;
  string alias;
};

struct LitEdge {
  string source;
  string target;
  string chan_point;
  string last_update;
  int capacity;
  int time_lock_delta;
  int min_htlc;
  int fee_base_msat;
  int fee_rate_milli_msat;
  string disabled;
  int component;
};

// typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
//                               LitVertex, LitEdge> LitGraph;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              LitVertex, LitEdge> LitGraph;

typedef graph_traits<LitGraph>::vertex_iterator vertex_iter;
typedef graph_traits<LitGraph>::vertex_descriptor Vertex;


void readgraph(LitGraph& g);
