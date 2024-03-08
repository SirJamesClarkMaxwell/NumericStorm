#include "pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;

namespace TestingSimplexPointOperations
{
    //* Testowanie funkcji setUp
    struct TestSetUpFunction : public ::testing::Test
    {
        UsefullyObjects usefullyObjects;
        SimplexPoint<4> testingSimplexPoint{usefullyObjects.referencedArray};
        testingSimplexPoint.setModel(usefullyObjects.gaussian, usefullyObjects.chi2Model);
    };

    TEST_F(TestSetUpFunction, settingModel)
    {
        EXPECT_TRUE(tetingSimplexPoint.);
        EXPECT_TRUE(tetingSimplexPoint);
    }
    //* testowanie rzucania błędów o nieustawieniu modelu i błedu modelu

    //* Testowanie funkcji calculateData
    //* Testowanie funkcji calculateError

    //! inny plik
    //* testowanie operatorów porównania
    //* testowanie konstruktora kopiującego

}
