#include "core/AngleRadians.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

namespace Core
{

AngleRadians::AngleRadians (int integerPart, int fractionalPart)
    : Pair (integerPart, fractionalPart)
{
  normalize ();
}

void
AngleRadians::increase (int val)
{
  second_ += val;
  normalize ();
}

void
AngleRadians::decrease (int val)
{
  second_ -= val;
  normalize ();
}

void
AngleRadians::normalize ()
{
  // Handle carry over from fractional to integer
  if (second_ >= PRECISION)
    {
      first_ += (second_ / PRECISION);
      second_ %= PRECISION;
    }

  // Handle borrowing for negatives
  while (second_ < 0)
    {
      second_ += PRECISION;
      first_--;
    }
}

std::string
AngleRadians::toString () const
{
  std::ostringstream oss;
  oss << first_ << "." << std::setfill ('0') << std::setw (3) << second_
      << " rad";
  return oss.str ();
}

} // namespace Core
