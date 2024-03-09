#include "pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;

namespace TestingSimplexPointOperations {

//* testing setUp method
struct TestSetUpFunction : public ::testing::Test, public UsefullyObjects
{};

TEST_F(TestSetUpFunction, settingModels)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    testingSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);

    bool expectedTrue = true;
    bool isSetModel = testingSimplexPoint.modelIsSet();
    bool isSetErrorModel = testingSimplexPoint.errorModelIsSet();
    EXPECT_TRUE(isSetModel == expectedTrue);
    EXPECT_TRUE(isSetErrorModel == expectedTrue);

    auto model = testingSimplexPoint.getModel();
    auto errorModel = testingSimplexPoint.getErrorModel();
    EXPECT_TRUE(model == sharedPtrModel);
    EXPECT_TRUE(errorModel == sharedPtrErrorModel);
}
TEST_F(TestSetUpFunction, checkingSetFalseMember)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    bool expectedFalse = false;
    bool isSetModel = testingSimplexPoint.modelIsSet();
    bool isSetErrorModel = testingSimplexPoint.errorModelIsSet();
    EXPECT_TRUE(isSetModel == expectedFalse);
    EXPECT_TRUE(isSetErrorModel == expectedFalse);
}
// * testing Model and ErrorModel as a derived class
TEST_F(TestSetUpFunction, settingModelsByDerivedClass)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    testingSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);

    bool expectedTrue = true;
    bool isSetModel = testingSimplexPoint.modelIsSet();
    bool isSetErrorModel = testingSimplexPoint.errorModelIsSet();
    EXPECT_TRUE(isSetModel == expectedTrue);
    EXPECT_TRUE(isSetErrorModel == expectedTrue);

    auto model = testingSimplexPoint.getModel();
    auto errorModel = testingSimplexPoint.getErrorModel();
    EXPECT_TRUE(model == sharedPtrModel);
    EXPECT_TRUE(errorModel == sharedPtrErrorModel);
}

//* testowanie rzucania błędów o nieustawieniu modelu i błedu modelu
TEST_F(TestSetUpFunction, throwingExceptionIfModelIsNotSet)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    const char* expectedMessage = "Model to calculating the data is not setted. \n Please set model as a Model object. \n To get more information check out our documetation.";
    try
    {
        //testingSimplexPoint.calculateData();
    }
    catch (const NoSetModelExeption& e)
    {
        EXPECT_STREQ(e.what(), expectedMessage);
    }
}

};
//* Testowanie funkcji calculateData
//* Testowanie funkcji calculateError

//! inny plik
//* testowanie operatorów porównania
//* testowanie konstruktora kopiującego

