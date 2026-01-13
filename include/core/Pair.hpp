#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>
#include <string>

namespace Core
{

/// @brief Represents the type of pair for identification in polymorphism
enum class PairType
{
  Base,
  Degrees,
  Radians
};

/// @brief Base class for a pair of integral numbers.
/// Following SOLID: This class handles basic storage and defines the
/// interface.
class Pair
{
protected:
  int first_;
  int second_;

public:
  /// @brief Constructor
  Pair (int f = 0, int s = 0) : first_ (f), second_ (s) {}

  /// @brief Virtual destructor is MANDATORY for base classes to prevent memory
  /// leaks
  virtual ~Pair () = default;

  // Field Accessors
  int
  getFirst () const
  {
    return first_;
  }
  int
  getSecond () const
  {
    return second_;
  }
  void
  setFirst (int f)
  {
    first_ = f;
  }
  void
  setSecond (int s)
  {
    second_ = s;
  }

  /// @brief Virtual function for increasing by a given value.
  virtual void increase (int val) = 0;

  /// @brief Virtual function for decreasing by a given value.
  virtual void decrease (int val) = 0;

  /// @brief Returns a string representation for UI/Console.
  virtual std::string toString () const = 0;

  /// @brief Returns the specific type of the derived class.
  virtual PairType
  getType () const
  {
    return PairType::Base;
  }
};

} // namespace Core

#endif // PAIR_H
