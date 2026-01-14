#include "core/AngleDegrees.hpp"
#include <iomanip>
#include <sstream>

namespace Core
{

AngleDegrees::AngleDegrees (First deg, Second min) : Pair (deg, min)
{
  normalize ();
}

void
AngleDegrees::increase (std::intmax_t val)
{
  second_ += Second{ val };
  normalize ();
}

void
AngleDegrees::decrease (std::intmax_t val)
{
  second_ -= Second{ val };
  normalize ();
}

void
AngleDegrees::normalize ()
{
  const std::intmax_t SECONDS_IN_MINUTE = 60;
  const std::intmax_t FULL_DEGREE_MINS = 21'600;

      intmax_t total
      = (static_cast<std::intmax_t> (first_) * SECONDS_IN_MINUTE)
        + static_cast<std::intmax_t> (second_);

  if (total < 0)
    {
      total = FULL_DEGREE_MINS + (total % FULL_DEGREE_MINS);
    }
  total %= FULL_DEGREE_MINS;

  first_ = First{ total / SECONDS_IN_MINUTE };
  second_ = Second{ total % SECONDS_IN_MINUTE };
}

std::string
AngleDegrees::toString () const
{
  std::ostringstream oss;
  oss << first_ << "° " << second_ << "'";
  return oss.str ();
}

} // namespace Core
