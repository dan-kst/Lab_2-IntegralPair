#include "core/Factory.hpp"
#include "core/Pair.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using namespace Core;

TEST (PolymorphismTest, BasePointerArrayTest)
{
  std::vector<std::unique_ptr<Pair> > shapes;

  shapes.push_back (
      NumberFactory::create (PairType::Degrees, First{ 10 }, Second{ 30 }));
  shapes.push_back (
      NumberFactory::create (PairType::Radians, First{ 2 }, Second{ 500 }));

  EXPECT_EQ (shapes[0]->getType (), PairType::Degrees);
  EXPECT_EQ (shapes[1]->getType (), PairType::Radians);

  for (auto &obj : shapes)
    {
      int initialFirst = obj->getFirst ();
      obj->increase (10);
      EXPECT_NE (obj->toString (), "");
    }
}
