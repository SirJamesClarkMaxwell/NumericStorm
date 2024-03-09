#pragma once
#include "pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;


namespace TestingSimplexPointCopyAndAssign
{
//* testing copy constructor
struct TestingCopyConstructor :public ::testing::Test, public UsefullyObjects
{
    TestingCopyConstructor()
        :baseSimplexPoint(arguments, referencedArray, additionalParameters), testingPoint(baseSimplexPoint) {};
    SimplexPoint<4> baseSimplexPoint;
    SimplexPoint<4> testingPoint;

};

TEST_F(TestingCopyConstructor, arguments)
{

    std::vector<double> expectedArguments = baseSimplexPoint.getArguments();
    std::vector<double> actualArguments = testingPoint.getArguments();
    EXPECT_EQ(expectedArguments, actualArguments);
}

//* testing assignment operator
}