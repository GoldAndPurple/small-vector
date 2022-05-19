#include <vec/vec.hpp>

#include <gtest/gtest.h>

TEST(SMALL_VEC, PUSH) {
  SmallVector<int, 4> four;
  four.push(1);
  ASSERT_EQ(1, four[0]);
  four.push(2);
  ASSERT_EQ(2, four[1]);
}