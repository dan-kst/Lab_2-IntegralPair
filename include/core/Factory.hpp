#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "AngleDegrees.hpp"
#include "AngleRadians.hpp"
#include "Pair.hpp"
#include <memory>
#include <stdexcept>

namespace Core
{

/// @brief Factory class to handle polymorphic creation of Pair-based objects.
/// Following SOLID: This implements the Factory Method pattern to decouple
/// the creation logic from the UI wrappers.
class NumberFactory
{
public:
  /// @brief Creates a specific object based on the PairType.
  /// @param type The type of object to create.
  /// @param f The first integral value (Degrees or Integer part).
  /// @param s The second integral value (Minutes or Fractional part).
  /// @return A unique_ptr to the created object.
  static std::unique_ptr<Pair>
  create (PairType type, First f, Second s)
  {
    switch (type)
      {
      case PairType::Degrees:
        return std::make_unique<AngleDegrees> (f, s);
      case PairType::Radians:
        return std::make_unique<AngleRadians> (f, s);
      case PairType::Base:
        throw std::invalid_argument ("Cannot instantiate abstract Base Pair.");
      default:
        throw std::invalid_argument ("Unknown PairType provided to Factory.");
      }
  }
};

} // namespace Core

#endif // FACTORY_HPP
