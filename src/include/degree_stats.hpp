/* Copyright (c) 2019 Kulpreet Singh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// The functions in this file are useful for implementing new
// algorithms and finding simple stats about the graph.

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

// A class that provides a function object for iterating over all
// vertices in the graph and printing the in/out degrees.
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

// For each vertex in the graph, set in/out/total degree in the
// vectors provided.
void get_degrees(vector<Degree> &in_degrees, vector<Degree> &out_degrees,
                 vector<Degree> &degrees, LitGraph &g) {
  graph_traits<LitGraph>::vertex_iterator i, end;
  for (boost::tie(i, end) = vertices(g); i != end; ++i) {
    in_degrees.push_back(in_degree(*i, g));
    out_degrees.push_back(out_degree(*i, g));
    degrees.push_back(degree(*i, g));
  }
}

// Compute simple stats about degrees for each vertex in the graph and
// print those.
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
