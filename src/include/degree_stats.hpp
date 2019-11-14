#ifndef LNCENTRALITY_DEGREE_STATS_HPP
#define LNCENTRALITY_DEGREE_STATS_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/graph/betweenness_centrality.hpp>

#include <fstream>
#include <numeric>

#include "readgraph.hpp"

using namespace boost::accumulators;

namespace lncentrality {

typedef graph_traits<LitGraph>::degree_size_type Degree;

template <class Graph> class degrees {
public:
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  typedef typename graph_traits<Graph>::degree_size_type Degree;

  degrees(Graph &g_) : g(g_) {}

  void operator()(const Vertex &v) const {
    using namespace boost;
    typename property_map<Graph, vertex_index_t>::type vertex_id =
        get(vertex_index, g);

    std::cout << "vertex: " << get(vertex_id, v) << " :: " << g[v].name
              << std::endl;

    std::cout << " in + out degree " << degree(v, g) << std::endl;
    std::cout << " out degree " << out_degree(v, g) << std::endl;
    std::cout << " in degree " << in_degree(v, g) << std::endl;
  }

private:
  Graph &g;
};

void get_degrees(vector<Degree> &in_degrees, vector<Degree> &out_degrees,
                 vector<Degree> &degrees, LitGraph &g) {
  graph_traits<LitGraph>::vertex_iterator i, end;
  for (boost::tie(i, end) = vertices(g); i != end; ++i) {
    in_degrees.push_back(in_degree(*i, g));
    out_degrees.push_back(out_degree(*i, g));
    degrees.push_back(degree(*i, g));
  }
}

map<string, double> get_degrees_stats(LitGraph &g) {
  graph_traits<LitGraph>::vertex_iterator i, end;
  accumulator_set<Degree, stats<tag::mean, tag::variance>> in_degrees,
      out_degrees, degrees;
  map<string, double> result;
  for (boost::tie(i, end) = vertices(g); i != end; ++i) {
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

} // namespace lncentrality

#endif
