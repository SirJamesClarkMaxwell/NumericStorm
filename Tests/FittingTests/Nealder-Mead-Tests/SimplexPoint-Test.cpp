#pragma once
#include "../pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;

namespace TestingSimplexPointOperations {

//* testing setUp method
struct TestingSimplexPoint : public ::testing::Test
{
    TestingSimplexPoint() {
        std::shared_ptr<Data> data_ptr = std::make_shared<Data>(objs.true_datum);
        testedPoint = SimplexPoint<4>{ data_ptr, objs.evaluatedArray };
        testedPoint.evaluatePoint(objs.gModel, objs.eModel, objs.additionalParameters);
    }


    UsefulObjects objs{};

    SimplexPoint<4> testedPoint{};
};



//* testing calculateData method
TEST_F(TestingSimplexPoint, evaluatingError)
{
    EXPECT_NEAR(testedPoint.getError(), objs.trueError, 0.01);
};



}

//! inny plik
//* testowanie operatorów porównania
//* testowanie konstruktora kopiującego

