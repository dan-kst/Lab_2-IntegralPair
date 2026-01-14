#include "core/AngleRadians.hpp"

namespace Core
{

AngleRadians::AngleRadians (First integerPart, Second fractionalPart)
    : Pair (integerPart, fractionalPart)
{
  normalize ();
}

void
AngleRadians::increase (std::intmax_t val)
{
  second_ += Second{ val };
  normalize ();
}

void
AngleRadians::decrease (std::intmax_t val)
{
  second_ -= Second{ val };
  normalize ();
}

void
AngleRadians::normalize ()
{
  auto rawFirst = static_cast<std::intmax_t> (first_);
  auto rawSecond = static_cast<std::intmax_t> (second_);

  if (rawSecond >= PRECISION)
    {
      rawFirst += (rawSecond / PRECISION);
      rawSecond %= PRECISION;
    }

  while (rawSecond < 0)
    {
      rawSecond += PRECISION;
      rawFirst--;
    }

  first_ = First{ rawFirst };
  second_ = Second{ rawSecond };
}

std::string
AngleRadians::toString () const
{
  auto rawFirst = static_cast<std::intmax_t> (first_);
  auto rawSecond = static_cast<std::intmax_t> (second_);
  std::ostringstream oss;
  oss << rawFirst << "." << std::setfill ('0') << std::setw (3) << rawSecond
      << " rad";
  return oss.str ();
}

} // namespace Core
