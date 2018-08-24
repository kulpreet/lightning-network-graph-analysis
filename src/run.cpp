#include "algos.hpp"

int main() {
  LitGraph g;
  readgraph(g);
  
  // boost::print_graph(g, get(&LitVertex::name, g), std::cout);

  // std::for_each(vertices(g).first, vertices(g).second,
  //                   exercise_vertex<LitGraph>(g));

  
  //boost::write_graphml(std::cout, g, dp);
  // std::for_each(vertices(g).first, vertices(g).second,
  //               degrees<LitGraph>(g));

  // vector<Degree> in_degrees, out_degrees, degrees;
  // get_degrees(in_degrees, out_degrees, degrees, g);
  // for (vector<Degree>::const_iterator i = in_degrees.begin(); i != in_degrees.end(); ++i) {
  //   std::cout << *i << ' ';
  // }
  // std::cout << endl;
  // for (vector<Degree>::const_iterator i = out_degrees.begin(); i != out_degrees.end(); ++i) {
  //   std::cout << *i << ' ';
  // }
  // std::cout << endl;
  // for (vector<Degree>::const_iterator i = degrees.begin(); i != degrees.end(); ++i) {
  //   std::cout << *i << ' ';
  // }
  // std::cout << endl;

  std::cout << "Number of vertices: " << num_vertices(g) << endl;

  // map<string, double> stats = get_degrees_stats(g);

  // for (map<string, double>::const_iterator i = stats.begin(); i != stats.end(); ++i) {
  //   std::cout << i->first << ' ' << i->second << endl;
  // }

  get_articulation_points(g);

  get_centrality(g);
  
  return 0;
}
