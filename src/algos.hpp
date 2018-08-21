#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include "readgraph.hpp"

using namespace boost::accumulators;

void print_edges_with_components(LitGraph& g){
  graph_traits<LitGraph>::vertex_descriptor src, tgt;
  graph_traits < LitGraph >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    src = source(*ei, g);
    tgt = target(*ei, g);  
    std::cout << g[src].name << " -- " 
              << g[tgt].name
              << " [label=\"" << g[*ei].component << "\"]\n";
    std::cout << "}\n";
  }
}

template <class Graph> struct compare_by_degree {
  compare_by_degree(Graph& g_) : g(g_) {}
  Graph& g;
  int operator() (const Vertex& a, const Vertex& b) const {
    return degree(a, g) > degree(b, g);
  }
};

template <class Graph> struct print_vertex {
  print_vertex(Graph& g_) : g(g_) {}
  Graph& g;
  void operator() (const Vertex& v) const {
    std::cout << "vertex: " << g[v].name
              << " :: " << g[v].pub_key
              << " :: " << degree(v, g)
              << std::endl;
  }
};

void get_articulation_points(LitGraph& g) {
  std::vector<Vertex> art_points;
  std::pair<std::size_t, std::back_insert_iterator<std::vector<Vertex> > >
    results = biconnected_components(g, get(&LitEdge::component, g), std::back_inserter(art_points));
  std::cout << "Found " << results.first << " biconnected components.\n";
  
  articulation_points(g, std::back_inserter(art_points));
  std::cout << "Found " << art_points.size() << " articulation points.\n";

  //print_edges_with_components(g);

  // sort articulation
  std::sort(art_points.begin(), art_points.end(), compare_by_degree<LitGraph>(g));
  // print top art points
  std::for_each(art_points.begin(), art_points.end(), print_vertex<LitGraph>(g));
}

template <class Graph> struct degrees {

  degrees(Graph& g_) : g(g_) { }
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  typedef typename graph_traits<Graph>::degree_size_type Degree;

  void operator()(const Vertex& v) const
  {
    using namespace boost;
    typename property_map<Graph, vertex_index_t>::type vertex_id = get(vertex_index, g);

    std::cout << "vertex: " << get(vertex_id, v) << " :: " << g[v].name << std::endl;

    std::cout << " in + out degree " << degree(v, g) << std::endl;
    std::cout << " out degree " << out_degree(v, g) << std::endl;    
    std::cout << " in degree " << in_degree(v, g) << std::endl;    
  }
  Graph& g;
};

typedef graph_traits<LitGraph>::degree_size_type Degree;

// return by value, count on RVO
void get_degrees(vector<Degree>& in_degrees, vector<Degree>& out_degrees, vector<Degree>& degrees, LitGraph& g) {  
  graph_traits<LitGraph>::vertex_iterator i, end;
  for (boost::tie(i,end) = vertices(g); i != end; ++i) {
    in_degrees.push_back(in_degree(*i, g));
    out_degrees.push_back(out_degree(*i, g));
    degrees.push_back(degree(*i, g));
  }
}

// return by value, count on RVO
map<string, double> get_degrees_stats(LitGraph& g) {  
  graph_traits<LitGraph>::vertex_iterator i, end;
  accumulator_set<Degree, stats<tag::mean, tag::variance > > in_degrees, out_degrees, degrees;
  map<string, double> result;
  for (boost::tie(i,end) = vertices(g); i != end; ++i) {
    in_degrees(in_degree(*i, g));
    out_degrees(out_degree(*i, g));
    degrees(degree(*i, g));
  }
  result["in_degrees_mean"] = mean(in_degrees);
  result["in_degrees_variance"] = variance(in_degrees);
  result["out_degrees_mean"] = mean(out_degrees);
  result["out_degrees_variance"] = variance(out_degrees);
  result["degrees_mean"] = mean(degrees);
  result["degrees_variance"] = variance(degrees);
  return result;
}

template <class Graph> struct exercise_vertex {
  exercise_vertex(Graph& g_) : g(g_) { }
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  void operator()(const Vertex& v) const
  {
    using namespace boost;
    typename property_map<Graph, vertex_index_t>::type vertex_id = get(vertex_index, g);

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
        std::cout << "(" << g[src].name
                  << "," << g[targ].name << ") ";
      }
    std::cout << std::endl;

    // // Write out the incoming edges
    // std::cout << "\tin-edges: ";
    // typename graph_traits<Graph>::in_edge_iterator in_i, in_end;
    // for (boost::tie(in_i, in_end) = in_edges(v, g); in_i != in_end; ++in_i)
    //   {
    //     e = *in_i;
    //     Vertex src = source(e, g), targ = target(e, g);
    //     std::cout << "(" << get(vertex_id, src)
    //               << "," << get(vertex_id, targ) << ") ";
    //   }
    // std::cout << std::endl;

    // // Write out all adjacent vertices
    // std::cout << "\tadjacent vertices: ";
    // typename graph_traits<Graph>::adjacency_iterator ai, ai_end;
    // for (boost::tie(ai,ai_end) = adjacent_vertices(v, g);  ai != ai_end; ++ai)
    //   std::cout << get(vertex_id, *ai) <<  " ";
    // std::cout << std::endl;
  }
  Graph& g;
};
