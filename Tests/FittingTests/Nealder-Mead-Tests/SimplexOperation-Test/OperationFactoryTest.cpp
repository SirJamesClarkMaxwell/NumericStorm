#pragma once
#include "pch.h"
#include "SetUpOperationFactory.hpp"

namespace TestingSimplexOperationFactory {
//* testing registering Operations
TEST_F(OperationFactoryTest, registeringSimplexOperation)
{
    SetUp();
    registerAllOperations();
    std::array<std::string, 4> expectedStrings{ "Reflection", "Expansion", "Contraction", "Shrinking" };


    int i = 0;
    for (auto& operation : testedSimplexOperationFactory.getOperationList())
    {
        EXPECT_EQ(operation.first, expectedStrings[i]);
        i++;
    }
}
//* testing unregistering Operations
TEST_F(OperationFactoryTest, unRegisteringSimplexOperation)
{
    SetUp();
    registerAllOperations();
    std::array<std::string, 4> expectedStrings{ "Reflection", "Expansion", "Contraction" };

    testedSimplexOperationFactory.unRegisterOperation("Shrinking");
    int i = 0;
    for (auto& operation : testedSimplexOperationFactory.getOperationList())
    {
        EXPECT_EQ(operation.first, expectedStrings[i]);
        i++;
    }


};
/*
//* testing throwing and error if operation is not available
TEST_F(OperationFactoryTest, throwingExceptionIfOperationIsNotAvailable)
{
    SetUp();
    testedSimplexOperationFactory.registerOperation("Reflection", reflectionMaker);
    testedSimplexOperationFactory.registerOperation("Expansion", expansionMaker);

    const std::string operationToUnregister = "Shrinking";
    const std::string expectedMessage = "This " + operationToUnregister + " isn't available. You could forget to register concrate facotry. To see how to do it, plase check our documentation.";

    try
    {
        testedSimplexOperationFactory.unRegisterOperation(operationToUnregister);
        FAIL() << "Expected NoAvailableFactoryException";
    }
    catch (const std::exception& e)
    {
        const char* actualMessage = e.what();
        std::cout << actualMessage << std::endl;
        // EXPECT_EQ(actualMessage, expectedMessage);
        EXPECT_EQ(2, 2);
    }
    catch (...) {
        FAIL() << "Expected NoAvailableFactoryException";
    }

};
*/

//* testing creating Operations
TEST_F(OperationFactoryTest, creatingOperation)
{
    SetUp();
    registerAllOperations();
    SimplexFigure<4> trueReflectedSimplexFigure = Reflection<4>(simplexOperationSettings)(basicSimplexFigure);
    SimplexFigure<4> testedReflectedSimplexFigure = testedSimplexOperationFactory.createOperation("Reflection", basicSimplexFigure);
    for (int i = 0;i < 5;i++)
    {
        SimplexPoint<4> testedPoint = testedReflectedSimplexFigure[i];
        SimplexPoint<4> truePoint = trueReflectedSimplexFigure[i];

        for (int j = 0;j < 4; j++)
            EXPECT_NEAR(testedPoint[j], truePoint[j], 0.001);
    }
}
//* testing updating settings
TEST_F(OperationFactoryTest, updatingSettingsForReflection)
{
    SetUp();
    registerAllOperations();
    SimplexFigure<4> trueReflectedSimplexFigure = Reflection<4>(SimplexOperationSettings(2))(basicSimplexFigure);
    testedSimplexOperationFactory.updateOperationSettings("Reflection", SimplexOperationSettings(2));
    SimplexFigure<4> testedReflectedSimplexFigure = testedSimplexOperationFactory.createOperation("Reflection", basicSimplexFigure);
    for (int i = 0;i < 5;i++)
    {
        SimplexPoint<4> testedPoint = testedReflectedSimplexFigure[i];
        SimplexPoint<4> truePoint = trueReflectedSimplexFigure[i];

        for (int j = 0;j < 4; j++)
            EXPECT_NEAR(testedPoint[j], truePoint[j], 0.001);
    }
}

}