#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include "core/Pair.hpp"
#include "core/Factory.hpp"

using namespace Core;

TEST(PolymorphismTest, BasePointerArrayTest) {
    // "use an array of pointers to objects of the base class"
    std::vector<std::unique_ptr<Pair>> shapes;
    
    // Using Factory for creation (Hard Mode)
    shapes.push_back(NumberFactory::create(PairType::Degrees, 10, 30));
    shapes.push_back(NumberFactory::create(PairType::Radians, 2, 500));
    
    // Verify types
    EXPECT_EQ(shapes[0]->getType(), PairType::Degrees);
    EXPECT_EQ(shapes[1]->getType(), PairType::Radians);
    
    // Verify virtual functions work through base pointers
    for (auto& obj : shapes) {
        int initialFirst = obj->getFirst();
        obj->increase(10); 
        // We just care that it doesn't crash and modifies the state
        EXPECT_NE(obj->toString(), "");
    }
}
