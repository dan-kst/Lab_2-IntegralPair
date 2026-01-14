#include "core/AngleRadians.hpp"
#include "core/Pair.hpp"
#include <gtest/gtest.h>

using namespace Core;

// --- AngleDegrees Tests ---

TEST (AngleRadiansTest, NormalizationTest)
{
  // 1500 fraction with 1000 precision should carry 1 to integer
  AngleRadians r (First{ 1 }, Second{ 1500 });
  EXPECT_EQ (r.getFirst (), First{ 2 });
  EXPECT_EQ (r.getSecond (), Second{ 500 });
}

TEST (AngleRadiansTest, BorrowTest)
{
  // 1.000 - 0.001 = 0.999
  AngleRadians r (First{ 1 }, Second{ 0 });
  r.decrease (1);
  EXPECT_EQ (r.getFirst (), First{ 0 });
  EXPECT_EQ (r.getSecond (), Second{ 999 });
}
