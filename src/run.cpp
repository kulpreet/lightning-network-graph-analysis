#include "algos.hpp"

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <boost/filesystem.hpp>

#include <fstream>

int main(int ac, char** av) {
  LitGraph g;
  string filename, stem;
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("input", po::value<string>(), "filename for the graphml file to process")
    ;
  
  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);    
  
  if (vm.count("help")) {
    cout << desc << "\n";
    return 0;
  }

  if (vm.count("input")) {
    filename = vm["input"].as<string>();
    boost::filesystem::path p(filename);
    stem = p.stem().string();
    cout << "Reading graph from " << filename << std::endl;
  } else {
    cout << "No input file provided" << std::endl;
    return 1;
  }

  try {
    std::ifstream fstream(filename);
    readgraph(g, fstream);
  } catch (std::exception& e) {
    cout << "Error reading file " << filename << endl;
    return 1;
  }
  
  // // boost::print_graph(g, get(&LitVertex::name, g), std::cout);

  // // std::for_each(vertices(g).first, vertices(g).second,
  // //                   exercise_vertex<LitGraph>(g));

  
  // //boost::write_graphml(std::cout, g, dp);
  // // std::for_each(vertices(g).first, vertices(g).second,
  // //               degrees<LitGraph>(g));

  // // vector<Degree> in_degrees, out_degrees, degrees;
  // // get_degrees(in_degrees, out_degrees, degrees, g);
  // // for (vector<Degree>::const_iterator i = in_degrees.begin(); i != in_degrees.end(); ++i) {
  // //   std::cout << *i << ' ';
  // // }
  // // std::cout << endl;
  // // for (vector<Degree>::const_iterator i = out_degrees.begin(); i != out_degrees.end(); ++i) {
  // //   std::cout << *i << ' ';
  // // }
  // // std::cout << endl;
  // // for (vector<Degree>::const_iterator i = degrees.begin(); i != degrees.end(); ++i) {
  // //   std::cout << *i << ' ';
  // // }
  // // std::cout << endl;

  // std::cout << "Number of vertices: " << num_vertices(g) << endl;

  // // map<string, double> stats = get_degrees_stats(g);

  // // for (map<string, double>::const_iterator i = stats.begin(); i != stats.end(); ++i) {
  // //   std::cout << i->first << ' ' << i->second << endl;
  // // }

  get_articulation_points(g, stem);

  get_centrality(g, stem);
  
  // return 0;
}
