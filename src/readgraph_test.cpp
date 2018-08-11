#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>

#include "algos.hpp"

namespace tt = boost::test_tools;
 
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
 
BOOST_FIXTURE_TEST_SUITE(Degrees, Graph)
 
BOOST_AUTO_TEST_CASE(degrees)
{
  vector<Degree> expected_in = boost::assign::list_of(1)(1)(2);
  vector<Degree> expected_out = boost::assign::list_of(2)(1)(1);
  vector<Degree> expected_total = boost::assign::list_of(3)(2)(3);

  vector<Degree> in_degrees, out_degrees, degrees;
  get_degrees(in_degrees, out_degrees, degrees, g);  
  BOOST_TEST(in_degrees == expected_in, tt::per_element());
  BOOST_TEST(out_degrees == expected_out, tt::per_element());
  BOOST_TEST(degrees == expected_total, tt::per_element());
}
  
BOOST_AUTO_TEST_SUITE_END()
