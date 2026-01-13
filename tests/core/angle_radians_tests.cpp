#include "core/AngleRadians.hpp"
#include "core/Pair.hpp"
#include <gtest/gtest.h>

using namespace Core;

// --- AngleDegrees Tests ---

TEST(AngleRadiansTest, NormalizationTest) {
    // 1500 fraction with 1000 precision should carry 1 to integer
    AngleRadians r(1, 1500);
    EXPECT_EQ(r.getFirst(), 2);
    EXPECT_EQ(r.getSecond(), 500);
}

TEST(AngleRadiansTest, BorrowTest) {
    // 1.000 - 0.001 = 0.999
    AngleRadians r(1, 0);
    r.decrease(1);
    EXPECT_EQ(r.getFirst(), 0);
    EXPECT_EQ(r.getSecond(), 999);
}
