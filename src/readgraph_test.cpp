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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures

#include <boost/assign/list_of.hpp>
#include <boost/test/unit_test.hpp>

#include "include/algos.hpp"
#include "include/degree_stats.hpp"
#include "include/vertex.hpp"

using namespace lncentrality;

namespace tt = boost::test_tools;

struct Graph {
  LitGraph g;

  Graph() {
    BOOST_TEST_MESSAGE("setup mass");
    readgraph(g, std::cin);
  }

  ~Graph() { BOOST_TEST_MESSAGE("teardown mass"); }
};

BOOST_FIXTURE_TEST_SUITE(Degrees, Graph)

BOOST_AUTO_TEST_CASE(degrees) {
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
