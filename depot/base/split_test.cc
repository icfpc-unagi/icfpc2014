// Author: Kentaro Imajo (@imos)

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "base/split.h"

TEST(Split, Split) {
  EXPECT_EQ(vector<string>({"a", "b", "c", "d", "e", "f"}),
            Split("a/b/c/d/e/f", "/", 0));
  EXPECT_EQ(vector<string>({"a/b/c/d/e/f"}),
            Split("a/b/c/d/e/f", "/", 1));
  EXPECT_EQ(vector<string>({"a", "b", "c/d/e/f"}),
            Split("a/b/c/d/e/f", "/", 3));
  EXPECT_EQ(vector<string>({"a", "b", "c", "d", "e", "f"}),
            Split("a/b/c/d/e/f", "/", 7));
}

TEST(Split, SplitWithoutLimit) {
  EXPECT_EQ(vector<string>({"abc", "ghi"}), Split("abcdefghi", "def"));
  EXPECT_EQ(vector<string>({"a", "b", "c", "d", "e", "f"}),
            Split("a/b/c/d/e/f", "/"));
  EXPECT_EQ(vector<string>({"", "", "aa"}), Split("aaaaaaaa", "aaa"));
  EXPECT_EQ(vector<string>({"", "x", "", ""}), Split("abcxabcabc", "abc"));
}

TEST(ReverseSplit, ReverseSplit) {
  EXPECT_EQ(vector<string>({"a", "b", "c", "d", "e", "f"}),
            ReverseSplit("a/b/c/d/e/f", "/", 0));
  EXPECT_EQ(vector<string>({"a/b/c/d/e/f"}),
            ReverseSplit("a/b/c/d/e/f", "/", 1));
  EXPECT_EQ(vector<string>({"a/b/c/d", "e", "f"}),
            ReverseSplit("a/b/c/d/e/f", "/", 3));
  EXPECT_EQ(vector<string>({"a", "b", "c", "d", "e", "f"}),
            ReverseSplit("a/b/c/d/e/f", "/", 7));
  EXPECT_EQ(vector<string>({"aa", "", ""}), ReverseSplit("aaaaaaaa", "aaa", 0));
  EXPECT_EQ(vector<string>({"", "x", "", ""}),
            ReverseSplit("abcxabcabc", "abc", 0));
}
