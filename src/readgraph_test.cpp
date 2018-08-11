#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>
#include "readgraph.hpp"
 
struct Graph
{
    LitGraph g;
 
    Graph()
    {
        BOOST_TEST_MESSAGE("setup mass");
        readgraph(g);
    }
 
    ~Graph()
    {
        BOOST_TEST_MESSAGE("teardown mass");
    }
};
 
BOOST_FIXTURE_TEST_SUITE(Physics, Graph)
 
BOOST_AUTO_TEST_CASE(readgraph)
{
    BOOST_CHECK(1 + 1 == 2);
}
  
BOOST_AUTO_TEST_SUITE_END()
