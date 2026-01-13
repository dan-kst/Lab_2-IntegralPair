#include "core/AngleDegrees.hpp"
#include <iomanip>
#include <sstream>

namespace Core
{

AngleDegrees::AngleDegrees (int deg, int min) : Pair (deg, min)
{
  normalize ();
}

void
AngleDegrees::increase (int val)
{
  second_ += val;
  normalize ();
}

void
AngleDegrees::decrease (int val)
{
  second_ -= val;
  normalize ();
}

void
AngleDegrees::normalize ()
{
  // 1. Convert everything to total minutes
  int totalMinutes = first_ * 60 + second_;

  // 2. Handle negative results (Modulo in C++ can be tricky with negatives)
  while (totalMinutes < 0)
    {
      totalMinutes += 360 * 60;
    }

  // 3. Wrap degrees around 360
  totalMinutes %= (360 * 60);

  // 4. Extract degrees and minutes
  first_ = totalMinutes / 60;
  second_ = totalMinutes % 60;
}

std::string
AngleDegrees::toString () const
{
  std::ostringstream oss;
  oss << first_ << "° " << second_ << "'";
  return oss.str ();
}

} // namespace Core
