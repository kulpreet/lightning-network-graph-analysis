// g++ readgrpah.cpp -lboost_graph -o readgraph

#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_utility.hpp>
#include <iostream>

using namespace boost;
using namespace std;

struct LitVertex {
  string name;
  string last_update;
  string alias;
};

struct LitEdge {
  string chan_point;
  string last_update;
  int capacity;
  int time_lock_delta;
  int min_htlc;
  int fee_base_msat;
  int fee_rate_milli_msat;
  string disabled;
  };

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                              LitVertex, LitEdge> LitGraph;

typedef graph_traits<LitGraph>::vertex_iterator vertex_iter;
typedef graph_traits<LitGraph>::vertex_descriptor Vertex;

template <class Graph> struct exercise_vertex {
  exercise_vertex(Graph& g_) : g(g_) { }
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  void operator()(const Vertex& v) const
  {
    using namespace boost;
    typename property_map<Graph, vertex_index_t>::type
      vertex_id = get(vertex_index, g);
    std::cout << "vertex: " << get(vertex_id, v) << std::endl;

    // Write out the outgoing edges
    std::cout << "\tout-edges: ";
    typename graph_traits<Graph>::out_edge_iterator out_i, out_end;
    typename graph_traits<Graph>::edge_descriptor e;
    for (boost::tie(out_i, out_end) = out_edges(v, g);
         out_i != out_end; ++out_i)
    {
      e = *out_i;
      Vertex src = source(e, g), targ = target(e, g);
      std::cout << "(" << get(vertex_id, src)
                << "," << get(vertex_id, targ) << ") ";
    }
    std::cout << std::endl;

    // Write out the incoming edges
    std::cout << "\tin-edges: ";
    typename graph_traits<Graph>::in_edge_iterator in_i, in_end;
    for (boost::tie(in_i, in_end) = in_edges(v, g); in_i != in_end; ++in_i)
    {
      e = *in_i;
      Vertex src = source(e, g), targ = target(e, g);
      std::cout << "(" << get(vertex_id, src)
                << "," << get(vertex_id, targ) << ") ";
    }
    std::cout << std::endl;

    // Write out all adjacent vertices
    std::cout << "\tadjacent vertices: ";
    typename graph_traits<Graph>::adjacency_iterator ai, ai_end;
    for (boost::tie(ai,ai_end) = adjacent_vertices(v, g);  ai != ai_end; ++ai)
      std::cout << get(vertex_id, *ai) <<  " ";
    std::cout << std::endl;
  }
  Graph& g;
};

int main() {
    LitGraph g;
    boost::dynamic_properties dp;
    dp.property("name", get(&LitVertex::name, g));

    dp.property("chan_point", get(&LitEdge::chan_point, g));
    dp.property("last_update", get(&LitEdge::last_update, g));
    dp.property("capacity", get(&LitEdge::capacity, g));
    dp.property("time_lock_delta", get(&LitEdge::time_lock_delta, g));
    dp.property("min_htlc", get(&LitEdge::min_htlc, g));
    dp.property("fee_base_msat", get(&LitEdge::fee_base_msat, g));
    dp.property("fee_rate_milli_msat", get(&LitEdge::fee_rate_milli_msat, g));
    dp.property("disabled", get(&LitEdge::disabled, g));
    
    boost::read_graphml(std::cin, g, dp);

    //boost::print_graph(g, get(&LitVertex::name, g), std::cout);

    //boost::write_graphml(std::cout, g, dp);
    std::for_each(vertices(g).first, vertices(g).second,
                   exercise_vertex<LitGraph>(g));

    return 0;
}
