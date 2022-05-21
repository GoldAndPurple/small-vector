#include <vec/vec.hpp>

#include <gtest/gtest.h>
namespace vec {

TEST(SMALL_VEC, WITHIN_INLINE_CAP) {
  SmallVector<int, 4> four;
  four.Push(0);
  ASSERT_EQ(0, four[0]);
  four.Push(1);
  ASSERT_EQ(1, four[1]);
}

TEST(SMALL_VEC, INCREASE_CAP) {
  SmallVector<int, 2> two;
  two.Push(0);
  two.Push(1);

  ASSERT_EQ(2,two.Size());
  ASSERT_EQ(2,two.Capacity());

  two.Push(2);
  ASSERT_EQ(2, two[2]);

  ASSERT_EQ(3,two.Size());
  ASSERT_EQ(4,two.Capacity());

  two.Push(3);
  two.Push(4);

  ASSERT_EQ(5,two.Size());
  ASSERT_EQ(8,two.Capacity());
}

}  // namespace vec