#ifndef LNCENTRALITY_SUPPORT_HPP
#define LNCENTRALITY_SUPPORT_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/graph/betweenness_centrality.hpp>

#include <fstream>
#include <numeric>

#include "readgraph.hpp"

namespace lncentrality {

struct centrality_s {
  string name;
  string pub_key;
  double centrality;
};


void print_edges_with_components(LitGraph &g) {
  graph_traits<LitGraph>::vertex_descriptor src, tgt;
  graph_traits<LitGraph>::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    src = source(*ei, g);
    tgt = target(*ei, g);
    if (degree(src, g) > 1 && degree(src, g) > 1) {
      std::cout << g[src].name << " -- " << g[tgt].name << " [label=\""
                << g[*ei].component << "\"]\n";
    }
  }
}

template <class centrality_s> class compare_by_centrality {
public:
  int operator()(const centrality_s &a, const centrality_s &b) const {
    return a.centrality > b.centrality;
  }
};

template <class Graph> class compare_by_degree {
public:
  compare_by_degree(Graph &g_) : g(g_) {}

  int operator()(const Vertex &a, const Vertex &b) const {
    return degree(a, g) > degree(b, g);
  }

private:
  Graph &g;
};

template <class Graph> class print_centrality_s {
public:
  void operator()(const centrality_s &s) const {
    std::cout << "\"" << s.name << "\""
              << "," << s.centrality << "," << s.pub_key << std::endl;
  }
};

template <class Graph> class print_vertex {
public:
  print_vertex(Graph &g_) : g(g_) {}
  void operator()(const Vertex &v) const {
    std::cout << "\"" << g[v].name << "\""
              << "," << degree(v, g) << "," << g[v].pub_key << std::endl;
  }

private:
  Graph &g;
};

} // namespace lncentrality

#endif
