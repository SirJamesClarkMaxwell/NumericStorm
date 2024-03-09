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
TEST_F(TestSetUpFunction, settingModelsByDerivedClass)

// * testing Model and ErrorModel as a derived class
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

//* testing throwing exception if model and error is not set
TEST_F(TestSetUpFunction, throwingExceptionIfModelIsNotSet)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    const char* expectedMessage = "Model to calculating the data is not setted. \n Please set model as a Model object. \n To get more information check out our documetation.";
    try
    {
        testingSimplexPoint.calculateData();
    }
    catch (const NoSetModelExeption& e)
    {
        EXPECT_STREQ(e.what(), expectedMessage);
    }
}
TEST_F(TestSetUpFunction, throwingExceptionIfErrorModelIsNotSet)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    const char* expectedMessage = "Function to calculating the error is not setted. \n Please set this error model as an object of ErrorModel. You could use one of our predefided error model. \n To get more information check out our documentation!";
    try
    {
        testingSimplexPoint.calculateError(referencedData);
    }
    catch (const NoSetErrorModelExeption& e)
    {
        EXPECT_STREQ(e.what(), expectedMessage);
    }

};

//* testing calculateData method
TEST_F(TestSetUpFunction, calculateDataMethodByRollClasses)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    testingSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);
    std::unique_ptr<Data> calculatedData = testingSimplexPoint.calculateData();
    auto testedData = (*calculatedData).getValues();
    auto trueData = (*referencedData).getValues();
    for (int i = 0; i < arguments.size(); i++)
    {
        EXPECT_NEAR(testedData[i], trueData[i], 0.001);
    }
};
TEST_F(TestSetUpFunction, calculateDataMethodByDerivedClasses)
{
    SimplexPoint<4> testingSimplexPoint(arguments, referencedArray, additionalParameters);
    testingSimplexPoint.setUp(gaussianModel, chi2ErrorModel);
    std::unique_ptr<Data> calculatedData = testingSimplexPoint.calculateData();
    auto testedData = (*calculatedData).getValues();
    auto trueData = (*referencedData).getValues();
    for (int i = 0; i < arguments.size(); i++)
    {
        EXPECT_NEAR(testedData[i], trueData[i], 0.001);
    }
};

//* Testowanie funkcji calculateError
TEST_F(TestSetUpFunction, calculateErrorByDerivedClasses)
{
    SimplexPoint<4> referencedSimplexPoint(arguments, referencedArray, additionalParameters);
    SimplexPoint<4> evaluatedSimplexPoint(arguments, evaluatedParameters, additionalParameters);
    referencedSimplexPoint.setUp(gaussianModel, chi2ErrorModel);
    evaluatedSimplexPoint.setUp(gaussianModel, chi2ErrorModel);
    std::unique_ptr<Data> referencedData_unique_ptr = referencedSimplexPoint.calculateData();
    std::shared_ptr<Data> referencedData = std::move(referencedData_unique_ptr);
    auto referencedValues = (*referencedData).getValues();
    evaluatedSimplexPoint.calculateError(referencedData);
    double testedError = evaluatedSimplexPoint.getError();

    EXPECT_NEAR(testedError, trueError, 0.001);
};

}

//! inny plik
//* testowanie operatorów porównania
//* testowanie konstruktora kopiującego

