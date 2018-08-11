#include "algos.hpp"

int main() {
  LitGraph g;
  readgraph(g);
  //boost::print_graph(g, get(&LitVertex::name, g), std::cout);
  
  //boost::write_graphml(std::cout, g, dp);
  std::for_each(vertices(g).first, vertices(g).second,
                degrees<LitGraph>(g));
  
  return 0;
}
