#include <gtest/gtest.h>

#include <kiwiparser/kiwiparser.hpp>
using namespace kiwiparser;

TEST(LibraryTest, Add) {
  // Consider adding more test cases
  EXPECT_EQ(add(2, 3), 5);
  EXPECT_EQ(add(-1, 1), 0);
  EXPECT_EQ(add(0, 0), 0);
  EXPECT_EQ(add(-2, -3), -5);
}
