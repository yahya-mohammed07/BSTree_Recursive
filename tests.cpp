#include "lib/bst.hpp"
#include <catch2/catch_test_macros.hpp>

bst_<float> nums{0, 3, 2, 5, 77, 33, -1, 88, 4, 1, -2, 0.5};

TEST_CASE("contains") {
  REQUIRE(nums.contains(44) == false);
  REQUIRE(nums.contains(23) == false);
  REQUIRE(nums.contains(88) == true);
  REQUIRE(nums.contains(0.5) == true);
}

TEST_CASE("depth") {
  REQUIRE(nums.depth(44) == 0);
  REQUIRE(nums.depth(23) == 0);
  REQUIRE(nums.depth(88) == 4);
  REQUIRE(nums.depth(2) == 2);
}

TEST_CASE("max and min") {
  REQUIRE(nums.max() == 88);
  REQUIRE(nums.min() == -2);
}

TEST_CASE("get parent") {
  REQUIRE(*nums.get_parent(88) == 77);
  REQUIRE(*nums.get_parent(3) == 0);
  REQUIRE(*nums.get_parent(1) == 2);
}

TEST_CASE("find") {
  REQUIRE(*nums.find(88) == 88);
  REQUIRE(*nums.find(3) == 3);
  REQUIRE(nums.find(22) == nums.end());
}

TEST_CASE("begin") { REQUIRE(*nums.begin() == -2); }

TEST_CASE("operator()++ & operator(int)++") {
  REQUIRE(*(++nums.find(5)) == 33);
  REQUIRE(*(nums.find(5)++) == 33);
}

TEST_CASE("make empty") {
  nums.burn_tree();
  REQUIRE(nums.empty() == true);
}