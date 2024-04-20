#include <utility/publisher.h>
#include <gtest/gtest.h>

// ./publisher_test --gtest_brief=1
TEST(PublisherTest, Ctor) {
  utility::Publisher p;
  EXPECT_EQ(0, p.events().size());
}
