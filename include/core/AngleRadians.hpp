#ifndef ANGLE_RADIANS_HPP
#define ANGLE_RADIANS_HPP

#include "Pair.hpp"

namespace Core
{

/// @brief Represents an angle in radians using integer and fractional parts.
/// first_ = integer part, second_ = fractional part (fixed precision).
class AngleRadians : public Pair
{
private:
  // How many digits of precision we represent in the second_ field
  // e.g., if precision is 1000, second_ = 141 represents 0.141
  static constexpr int PRECISION = 1000;

public:
  AngleRadians (int integerPart = 0, int fractionalPart = 0);

  /// @brief Adds to the fractional part and carries over to integer.
  void increase (int val) override;

  /// @brief Subtracts from the fractional part and borrows from integer.
  void decrease (int val) override;

  std::string toString () const override;

  PairType
  getType () const override
  {
    return PairType::Radians;
  }

private:
  void normalize ();
};

} // namespace Core

#endif // ANGLE_RADIANS_HPP
