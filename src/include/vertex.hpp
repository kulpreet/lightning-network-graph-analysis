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

#ifndef LNCENTRALITY_VERTEX_HPP
#define LNCENTRALITY_VERTEX_HPP

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

// function object for printing debug information about a vertex
template <class Graph> class exercise_vertex {
public:
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;

    exercise_vertex(Graph &g_) : g(g_) {}

    void operator()(const Vertex &v) const {
        using namespace boost;
        typename property_map<Graph, vertex_index_t>::type vertex_id =
            get(vertex_index, g);

        std::cout << "vertex: " << get(vertex_id, v) << std::endl;

        // Print out the outgoing edges
        std::cout << "\tout-edges: ";
        typename graph_traits<Graph>::out_edge_iterator out_i, out_end;
        typename graph_traits<Graph>::edge_descriptor e;
        for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end;
             ++out_i) {
            e = *out_i;
            Vertex src = source(e, g), targ = target(e, g);
            std::cout << "(" << g[src].name << "," << g[targ].name << ") ";
        }
        std::cout << std::endl;
  }

private:
  Graph &g;
};
} // name space lncentrality

#endif
