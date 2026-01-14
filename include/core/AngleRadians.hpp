#ifndef ANGLE_RADIANS_HPP
#define ANGLE_RADIANS_HPP

#include "Pair.hpp"
#include <iomanip>

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
  AngleRadians (First integerPart = First{ 0 },
                Second fractionalPart = Second{ 0 });

  /// @brief Adds to the fractional part and carries over to integer.
  void increase (std::intmax_t val) override;

  /// @brief Subtracts from the fractional part and borrows from integer.
  void decrease (std::intmax_t val) override;

  [[nodiscard]] auto toString () const -> std::string override;

  [[nodiscard]] auto
  getType () const -> PairType override
  {
    return PairType::Radians;
  }

private:
  void normalize ();
};

} // namespace Core

#endif // ANGLE_RADIANS_HPP
