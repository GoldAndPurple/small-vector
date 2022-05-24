#include <vec/vec.hpp>

#include <gtest/gtest.h>

namespace vec {

class Mockup {
 public:
  float f_;
  std::string s_;

  Mockup(float f = 0.0, std::string s = "zero") : f_(f), s_(s) {}
};

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

  ASSERT_EQ(2, two.Size());
  ASSERT_EQ(2, two.Capacity());

  two.Push(2);
  ASSERT_EQ(2, two[2]);

  ASSERT_EQ(3, two.Size());
  ASSERT_EQ(4, two.Capacity());

  two.Push(3);
  two.Push(4);

  ASSERT_EQ(5, two.Size());
  ASSERT_EQ(8, two.Capacity());
}

TEST(SMALL_VEC, ITERATOR) {
  SmallVector<int, 2> two;
  std::stringstream out;

  two.Push(0);
  two.Push(1);
  for (auto element : two) {
    out << element << " ";
  }
  ASSERT_STREQ("0 1 ", out.str().c_str());
  out.str("");
  out.clear();

  two.Push(2);
  two.Push(3);
  two.Push(4);
  for (auto element : two) {
    out << element << " ";
  }
  ASSERT_STREQ("0 1 2 3 4 ", out.str().c_str());
}

TEST(SMALL_VEC, CUSTOM_CLASS) {
  SmallVector<Mockup, 2> two;
  std::stringstream out;
  out << std::setprecision(3);

  two.Push(Mockup(1.1, "point one"));
  two.Push(Mockup(7.0, "seven"));
  two.Push(Mockup(99.9, "nnn"));
  for (auto element : two) {
    out << element.f_ << '(' << element.s_ << ") ";
  }
  ASSERT_STREQ("1.1(point one) 7(seven) 99.9(nnn) ", out.str().c_str());
  out.str("");
  out.clear();
}

}  // namespace vec