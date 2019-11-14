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

#ifndef LNCENTRALITY_ALGOS_HPP
#define LNCENTRALITY_ALGOS_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/graph/betweenness_centrality.hpp>

#include <fstream>
#include <numeric>

#include "readgraph.hpp"
#include "support.hpp"

using namespace boost::accumulators;

namespace lncentrality {

void get_centrality(LitGraph &g, string &stem, string &outdir) {
  std::ofstream out;
  std::vector<double> centrality(num_vertices(g));
  graph_traits<LitGraph>::vertex_iterator i, end;

  std::vector<centrality_s> centrality_vector(num_vertices(g));

  brandes_betweenness_centrality(
      g, centrality_map(make_iterator_property_map(
                            centrality.begin(), get(vertex_index, g), double()))
             .vertex_index_map(get(vertex_index, g)));

  relative_betweenness_centrality(
      g, make_iterator_property_map(centrality.begin(), get(vertex_index, g),
                                    double()));

  for (boost::tie(i, end) = vertices(g); i != end; ++i) {
    centrality_s c = {g[*i].name, g[*i].pub_key, centrality[*i]};
    centrality_vector.push_back(c);
    // std::cout << g[*i].name << " :: "
    //           << g[*i].pub_key << " :: "
    //           << centrality[*i] << endl;
  }

  // sort centrality vector
  std::sort(centrality_vector.begin(), centrality_vector.end(),
            compare_by_centrality<centrality_s>());

  out.open(outdir + "/" + stem + ".centrality.csv",
           std::fstream::out | std::fstream::trunc);

  out << "alias,centrality,pub_key" << std::endl;
  for (std::vector<centrality_s>::iterator centrality_iter =
           centrality_vector.begin();
       centrality_iter != centrality_vector.begin() + 50; centrality_iter++) {
    out << "\"" << centrality_iter->name << "\""
        << "," << centrality_iter->centrality << "," << centrality_iter->pub_key
        << std::endl;
  }
  out.close();

  double dominance = central_point_dominance(
      g, make_iterator_property_map(centrality.begin(), get(vertex_index, g),
                                    double()));
  out.open(outdir + "/cpd.csv", std::fstream::out | std::fstream::app);
  out << stem << "," << dominance << std::endl;
  out.close();
}

void sort_and_print_art_points(std::vector<Vertex> &art_points, LitGraph &g,
                               string &stem, string &outdir) {
  std::ofstream out;
  out.open(outdir + "/" + stem + ".all_ap.csv",
           std::fstream::out | std::fstream::trunc);

  out << "alias,degree,pub_key" << std::endl;
  std::sort(art_points.begin(), art_points.end(),
            compare_by_degree<LitGraph>(g));
  // print top art points
  std::for_each(art_points.begin(), art_points.end(), [&out, &g](Vertex &v) {
    out << "\"" << g[v].name << "\""
        << "," << degree(v, g) << "," << g[v].pub_key << std::endl;
  });

  out.close();
}

void find_non_singleton_components(std::vector<Vertex> &art_points, LitGraph &g,
                                   string &stem, string &outdir) {

  // make a map component id to component size
  std::map<int, int> component_sizes;
  std::vector<Vertex>::iterator i;
  std::ofstream out;

  graph_traits<LitGraph>::edge_iterator ei, ei_end;
  graph_traits<LitGraph>::out_edge_iterator out_i, out_end;

  typedef graph_traits<LitGraph>::edge_descriptor Edge;
  std::vector<Edge> bridges;
  std::set<int> component_ids;
  std::map<int, set<int>> interesting_art_points;
  int num_interesting;

  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    component_sizes[g[*ei].component]++;
  }

  // iterate over all edges
  // select those edges where component size on both vertices are greater than 1
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    if (component_sizes[g[*ei].component] == 1) {
      bridges.push_back(*ei);
    }
  }

  // iterate over all art points
  for (i = art_points.begin(); i != art_points.end(); i++) {
    // get all the components for all the edges of the art points
    component_ids.clear();
    for (boost::tie(out_i, out_end) = out_edges(*i, g); out_i != out_end;
         ++out_i) {
      component_ids.insert(g[*out_i].component);
    }
    // find the number of components the art point is connecting
    num_interesting =
        std::accumulate(component_ids.begin(), component_ids.end(), 0,
                        [&component_sizes](int a, int cid) {
                          if (component_sizes[cid] > 5) {
                            a = a + 1;
                          }
                          return a;
                        });
    // std::cout << "art point " << *i << " num components = " <<
    // component_ids.size() << std::endl; std::cout << "art point " << *i << "
    // num interesting = " << num_interesting << std::endl; return art points
    // that have 2 or more components with size > 1/2/3/4/5
    if (num_interesting > 1) {
      // std::cout << "art point is an interesting art point " << *i <<
      // std::endl;
      interesting_art_points[*i] = component_ids;
    }
  }

  // date, #components, #interesting art points
  out.open(outdir + "/key_ap_stats.csv", std::fstream::out | std::fstream::app);
  out << stem << "," << component_sizes.size() << ","
      << interesting_art_points.size() << std::endl;
  out.close();

  out.open(outdir + "/" + stem + ".key_ap.csv",
           std::fstream::out | std::fstream::trunc);

  // Key Articulation Points
  out << "alias,num components,degree,pub_key" << std::endl;
  for (std::map<int, set<int>>::iterator x = interesting_art_points.begin();
       x != interesting_art_points.end(); x++) {
    out << "\"" << g[x->first].name << "\""
        << "," << (x->second).size() << "," << degree(x->first, g) << ","
        << g[x->first].pub_key << endl;
  }
  out.close();
}

void get_articulation_points(LitGraph &g, string &stem, string &outdir) {
  std::ofstream out;
  std::vector<Vertex> art_points;
  std::pair<std::size_t, std::back_insert_iterator<std::vector<Vertex>>>
      results = biconnected_components(g, get(&LitEdge::component, g),
                                       std::back_inserter(art_points));

  // date, #components, #interesting art points
  out.open(outdir + "/all_ap_stats.csv", std::fstream::out | std::fstream::app);
  out << stem << "," << results.first << "," << art_points.size() << std::endl;
  out.close();

  find_non_singleton_components(art_points, g, stem, outdir);
  sort_and_print_art_points(art_points, g, stem, outdir);
}

} // namespace lncentrality

#endif
