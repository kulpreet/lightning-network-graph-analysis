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

#ifndef LNCENTRALITY_READGRAPH_HPP
#define LNCENTRALITY_READGRAPH_HPP

#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphml.hpp>
#include <iostream>

using namespace boost;
using namespace std;

namespace lncentrality {

struct LitVertex {
  string id;
  string pub_key;
  string name;
  string last_update;
  string alias;
};

struct LitEdge {
  string id;
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

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              LitVertex, LitEdge>
    LitGraph;

typedef graph_traits<LitGraph>::vertex_iterator vertex_iter;
typedef graph_traits<LitGraph>::vertex_descriptor Vertex;

void readgraph(LitGraph &g, std::istream &filestream);

} // namespace lncentrality

#endif
