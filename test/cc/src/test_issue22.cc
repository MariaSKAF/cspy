
#include <memory>
#include <numeric>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"
#include "src/cc/bidirectional.h"

namespace bidirectional {

class TestIssue22 : public ::testing::Test {
 protected:
  const bool                     elementary      = true;
  const int                      number_vertices = 5;
  const int                      number_edges    = 8;
  const std::vector<double>      max_res         = {8.0, 2.0};
  const std::vector<double>      min_res         = {0.0, 0.0};
  std::unique_ptr<BiDirectional> bidirectional;
  const std::vector<int>         final_path = {0, 2, 1, 4};
  const std::vector<double>      final_res  = {3.0, 2.0};
  const double                   final_cost = -10.0;
};

void createGraphIssue22(BiDirectional* bidirectional) {
  bidirectional->addNodes({0, 1, 2, 3, 4});
  bidirectional->addEdge(0, 1, 10, {1, 1});
  bidirectional->addEdge(0, 2, 10, {1, 1});
  bidirectional->addEdge(0, 3, 10, {1, 1});
  bidirectional->addEdge(1, 4, -10, {1, 0});
  bidirectional->addEdge(2, 4, -10, {1, 0});
  bidirectional->addEdge(3, 4, -10, {1, 0});
  bidirectional->addEdge(3, 2, -5, {1, 1});
  bidirectional->addEdge(2, 1, -10, {1, 1});
}

TEST_F(TestIssue22, testBoth) {
  bidirectional = std::make_unique<BiDirectional>(
      number_vertices, number_edges, 0, 4, max_res, min_res);
  createGraphIssue22(bidirectional.get());

  bidirectional->run();

  auto path = bidirectional->getPath();
  auto res  = bidirectional->getConsumedResources();
  auto cost = bidirectional->getTotalCost();

  ASSERT_EQ(path, final_path);
  ASSERT_EQ(res, final_res);
  ASSERT_EQ(cost, final_cost);
}

} // namespace bidirectional
