#include "algos.hpp"

int main() {
  LitGraph g;
  readgraph(g);
  //boost::print_graph(g, get(&LitVertex::name, g), std::cout);
  
  //boost::write_graphml(std::cout, g, dp);
  std::for_each(vertices(g).first, vertices(g).second,
                degrees<LitGraph>(g));

  vector<Degree> in_degrees, out_degrees, degrees;
  get_degrees(in_degrees, out_degrees, degrees, g);
  for (vector<Degree>::const_iterator i = in_degrees.begin(); i != in_degrees.end(); ++i) {
    std::cout << *i << ' ';
  }
  std::cout << endl;
  for (vector<Degree>::const_iterator i = out_degrees.begin(); i != out_degrees.end(); ++i) {
    std::cout << *i << ' ';
  }
  std::cout << endl;
  for (vector<Degree>::const_iterator i = degrees.begin(); i != degrees.end(); ++i) {
    std::cout << *i << ' ';
  }
  std::cout << endl;
 
  return 0;
}
