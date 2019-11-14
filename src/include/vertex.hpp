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

template <class Graph> class exercise_vertex {
public:
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;

    exercise_vertex(Graph &g_) : g(g_) {}

    void operator()(const Vertex &v) const {
        using namespace boost;
        typename property_map<Graph, vertex_index_t>::type vertex_id =
            get(vertex_index, g);

        std::cout << "vertex: " << get(vertex_id, v) << std::endl;

        // Write out the outgoing edges
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
