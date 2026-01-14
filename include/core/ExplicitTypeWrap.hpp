
namespace Core
{
/// @brief A wrapper around a primitive that gives it a unique identity.
/// This ensures the compiler treats same types as completely different things.
template <typename T, typename Tag> struct StrongType
{
  T value;

  explicit StrongType (T val) : value (val) {}

  operator T () const { return value; }

  auto
  operator+= (const StrongType &n)
  {
    value += n.value;
    return *this;
  }
  auto
  operator-= (const StrongType &n)
  {
    value -= n.value;
    return *this;
  }

  friend auto
  operator+ (StrongType lhs, const StrongType &rhs) -> StrongType
  {
    lhs.value += rhs.value;
    return lhs;
  }
  friend auto
  operator% (StrongType lhs, const StrongType &rhs) -> StrongType
  {
    lhs.value %= rhs.value;
    return lhs;
  }
};
}
