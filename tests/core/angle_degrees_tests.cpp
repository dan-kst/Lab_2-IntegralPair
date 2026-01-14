#include "core/AngleDegrees.hpp"
#include "core/Pair.hpp"
#include <gtest/gtest.h>

using namespace Core;

// --- AngleDegrees Tests ---

TEST (AngleDegreesTest, NormalizationTest)
{
  // 70 minutes should become 1 degree 10 minutes
  AngleDegrees d (First{ 0 }, Second{ 70 });
  EXPECT_EQ (d.getFirst (), 1);
  EXPECT_EQ (d.getSecond (), 10);

  // 361 degrees should become 1 degree
  AngleDegrees d2 (First{ 361 }, Second{ 0 });
  EXPECT_EQ (d2.getFirst (), First{ 1 });
}

TEST (AngleDegreesTest, UnderflowTest)
{
  // -1 minute should wrap to 359 deg 59 min
  AngleDegrees d (First{ 0 }, Second{ 0 });
  d.decrease (1);
  EXPECT_EQ (d.getFirst (), First{ 359 });
  EXPECT_EQ (d.getSecond (), First{ 59 });
}
