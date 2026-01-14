#ifndef PAIR_HPP
#define PAIR_HPP

#include "ExplicitTypeWrap.hpp"
#include <cstdint>
#include <iostream>
#include <string>

namespace Core
{
struct [[nodiscard]] FirstTag
{
};
struct [[nodiscard]] SecondTag
{
};

using First = StrongType<std::intmax_t, FirstTag>;
using Second = StrongType<std::intmax_t, SecondTag>;

/// @brief Represents the type of pair for identification in polymorphism
enum class [[nodiscard]] PairType : std::uint8_t
{
  Base,
  Degrees,
  Radians
};

/// @brief Base class for a pair of integral numbers.
/// Following SOLID: This class handles basic storage and defines the
/// interface.
class [[nodiscard]] Pair
{
protected:
  First first_;
  Second second_;

public:
  /// @brief Constructor
  Pair (First f = First{ 0 }, Second s = Second{ 0 }) : first_ (f), second_ (s)
  {
  }

  /// @brief Virtual destructor is MANDATORY for base classes to prevent memory
  /// leaks
  virtual ~Pair () = default;

  // Field Accessors
  [[nodiscard]] auto
  getFirst () const -> First
  {
    return first_;
  }
  [[nodiscard]] auto
  getSecond () const -> Second
  {
    return second_;
  }
  void
  setFirst (First f)
  {
    first_ = f;
  }
  void
  setSecond (Second s)
  {
    second_ = s;
  }

  /// @brief Virtual function for increasing by a given value.
  virtual void increase (std::intmax_t val) = 0;

  /// @brief Virtual function for decreasing by a given value.
  virtual void decrease (std::intmax_t val) = 0;

  /// @brief Returns a string representation for UI/Console.
  [[nodiscard]] auto virtual toString () const -> std::string = 0;

  /// @brief Returns the specific type of the derived class.
  [[nodiscard]] auto virtual getType () const -> PairType
  {
    return PairType::Base;
  }
};

} // namespace Core

#endif // PAIR_H
