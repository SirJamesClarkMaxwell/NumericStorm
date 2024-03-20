#pragma once
#include "pch.h"
#include "SetUpOperationFactory.hpp"

namespace TestingSimplexOperationFactory {
TEST_F(OperationFactoryTest, registeringSimplexOperation)
{
    SetUp();
    std::array<std::string, 4> expectedStrings{ "Reflection", "Expansion", "Contraction", "Shrinking" };
    testedSimplexOperationFactory.registerOperation("Reflection", reflectionMaker);
    testedSimplexOperationFactory.registerOperation("Expansion", expansionMaker);
    testedSimplexOperationFactory.registerOperation("Contraction", contractionMaker);
    testedSimplexOperationFactory.registerOperation("Shrinking", shrinkingMaker);

    int i = 0;
    for (auto& operation : testedSimplexOperationFactory.getOperationList())
    {
        EXPECT_EQ(operation.first, expectedStrings[i]);
        i++;
    }
}
//* testing registering Operations
//* testing unregistering Operations

//* testing creating Operations
//* testing updating settings

}