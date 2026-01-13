#include <gtest/gtest.h>
#include "core/Pair.hpp"
#include "core/AngleDegrees.hpp"

using namespace Core;

// --- AngleDegrees Tests ---

TEST(AngleDegreesTest, NormalizationTest) {
    // 70 minutes should become 1 degree 10 minutes
    AngleDegrees d(0, 70);
    EXPECT_EQ(d.getFirst(), 1);
    EXPECT_EQ(d.getSecond(), 10);
    
    // 361 degrees should become 1 degree
    AngleDegrees d2(361, 0);
    EXPECT_EQ(d2.getFirst(), 1);
}

TEST(AngleDegreesTest, UnderflowTest) {
    // -1 minute should wrap to 359 deg 59 min
    AngleDegrees d(0, 0);
    d.decrease(1);
    EXPECT_EQ(d.getFirst(), 359);
    EXPECT_EQ(d.getSecond(), 59);
}
