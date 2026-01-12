#ifndef ANGLE_DEGREES_HPP
#define ANGLE_DEGREES_HPP

#include "Pair.hpp"

namespace Core
{

/// @brief Represents an angle in degrees and minutes.
/// first_ = degrees, second_ = minutes.
class AngleDegrees : public Pair
{
public:
    /// @brief Constructor with normalization (e.g., 70 minutes -> 1 degree 10 minutes)
    AngleDegrees(int deg = 0, int min = 0);

    /// @brief Increase total minutes, then normalize.
    void increase(int val) override;

    /// @brief Decrease total minutes, then normalize.
    void decrease(int val) override;

    std::string toString() const override;
    
    PairType getType() const override { return PairType::Degrees; }

private:
    /// @brief Logic to handle overflows (60 mins = 1 deg, 360 deg = 0 deg)
    void normalize();
};

} // namespace Core

#endif // ANGLE_DEGREES_HPP
