#include "pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;

namespace TestingSimplexPointOperations {
//* Testowanie funkcji setUp
struct TestSetUpFunction : public ::testing::Test, public UsefullyObjects
{};

TEST_F(TestSetUpFunction, settingModel)
{
    SimplexPoint<4> testingSimplexPoint(referencedArray, additionalParameters);
    testingSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);
    bool expectedTrue = true;
    bool isSetModel = testingSimplexPoint.modelIsSet();
    bool isSetErrorModel = testingSimplexPoint.errorModelIsSet();
    auto model = testingSimplexPoint.getModel();
    auto errorModel = testingSimplexPoint.getErrorModel();
    EXPECT_TRUE(isSetModel == expectedTrue);
    EXPECT_TRUE(isSetErrorModel == expectedTrue);
    EXPECT_TRUE(model == sharedPtrModel);
    EXPECT_TRUE(errorModel == sharedPtrErrorModel);
}
//* testowanie rzucania błędów o nieustawieniu modelu i błedu modelu

//* Testowanie funkcji calculateData
//* Testowanie funkcji calculateError

//! inny plik
//* testowanie operatorów porównania
//* testowanie konstruktora kopiującego

}
