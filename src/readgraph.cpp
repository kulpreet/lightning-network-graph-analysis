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

#include "include/readgraph.hpp"
#include <fstream>

namespace lncentrality {

// Given a LitGraph, builds BGL properties to be captured at each node
// of the graph.
boost::dynamic_properties build_properties(LitGraph &g) {

  boost::dynamic_properties dp;
  dp.property("name", get(&LitVertex::name, g));
  dp.property("pub_key", get(&LitVertex::pub_key, g));

  dp.property("source", get(&LitEdge::source, g));
  dp.property("target", get(&LitEdge::target, g));

  dp.property("chan_point", get(&LitEdge::chan_point, g));
  dp.property("last_update", get(&LitEdge::last_update, g));
  dp.property("capacity", get(&LitEdge::capacity, g));

  dp.property("time_lock_delta", get(&LitEdge::time_lock_delta, g));
  dp.property("min_htlc", get(&LitEdge::min_htlc, g));
  dp.property("fee_base_msat", get(&LitEdge::fee_base_msat, g));
  dp.property("fee_rate_milli_msat", get(&LitEdge::fee_rate_milli_msat, g));
  dp.property("disabled", get(&LitEdge::disabled, g));

  return dp;
};

void readgraph(LitGraph &g, std::istream &filestream) {
  boost::dynamic_properties dp = build_properties(g);
  boost::read_graphml(filestream, g, dp);
};

} // namespace lncentrality
