#include "count.h"

#include <gtest/gtest.h>

#include <string>

TEST(Count, Count22)
{
std::string str = "problems check";
size_t size = count(str);
size_t size2 = str.size();
EXPECT_EQ(size,size2);
}

