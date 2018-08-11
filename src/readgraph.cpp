#include "readgraph.hpp"

boost::dynamic_properties build_properties(LitGraph& g) {
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

  return dp;
};
                                           
void readgraph(LitGraph& g) {
  std::cout << "reading graph..." << std::endl;
  boost::dynamic_properties dp = build_properties(g);
  boost::read_graphml(std::cin, g, dp);
};
