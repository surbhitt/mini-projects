#include <gtest/gtest.h>
#include "lvsh_dist.cpp"

TEST(LvshtTest, LvshDist1) {
    EXPECT_EQ(1, lvsh_dist("bello", "hello"));
}

TEST(LvshtTest, LvshDist2) {
   EXPECT_EQ(3, lvsh_dist("kitten", "sitting"));
}

TEST(LvshtTest, LvshDist3) {
   EXPECT_EQ(0, lvsh_dist("abcde", "abcde"));
}

TEST(LvshtTest, LvshDist4) {
   EXPECT_EQ(1, lvsh_dist("abcde", "acbde"));
}

TEST(LvshtTest, LvshDist5) {
   EXPECT_EQ(4, lvsh_dist("abcde", "abbcd"));
}

TEST(LvshtTest, LvshDist6) {
   EXPECT_EQ(6, lvsh_dist("abcde", "fgh"));
}

int main (int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


