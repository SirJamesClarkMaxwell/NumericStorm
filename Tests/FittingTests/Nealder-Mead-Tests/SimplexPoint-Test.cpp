#include "pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;

namespace TestingSimplexPointOperations {
//* Testowanie funkcji setUp
struct TestSetUpFunction : public ::testing::Test, public UsefullyObjects
{
    // std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
    // std::array<double, 4> evaluatedArray{ 1, 1, 1, -1 };

    // Parameters<4> referencedParameters{ referencedArray };
    // Parameters<4> evaluatedParameters{ evaluatedArray };

    // std::vector<double> arguments{ -2, -1, 0, 1, 2 };
    // AdditionalParameters additionalParameters{};
    // std::shared_ptr<Data> referencedData;
    // std::shared_ptr<Data> evaluatedData;

    // std::function<double(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData)> chi2Model = chi2ErrorModelFunction;
    // std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)> gaussianModel = gaussian;
    // double trueError;
    // void setUp() {
    //     referencedData = gaussian(arguments, referencedParameters, additionalParameters);
    //     evaluatedData = gaussian(arguments, evaluatedParameters, additionalParameters);
    //     double trueError = chi2ErrorModelFunction(referencedData, evaluatedData);

    // }

};

TEST_F(TestSetUpFunction, settingModel)
{
#define DEBUG = true;
    // setUp();
    Model<4> gaussianModel(gaussianModel);
    ErrorModel chi2ErrorModel(chi2Model);
    std::shared_ptr<Model<4>> sharedPtrModel = std::make_shared<Model<4>>(gaussianModel);
    std::shared_ptr<ErrorModel> sharedPtrErrorModel = std::make_shared<ErrorModel>(chi2ErrorModel);
    SimplexPoint<4> testingSimplexPoint(referencedArray, additionalParameters);
    testingSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);
    bool var1 = true;
    bool var2 = testingSimplexPoint.modelIsSet();
    bool var3 = testingSimplexPoint.errorModelIsSet();
    EXPECT_TRUE(var2 == var1);
    EXPECT_TRUE(var3 == var1);
}
//* testowanie rzucania błędów o nieustawieniu modelu i błedu modelu

//* Testowanie funkcji calculateData
//* Testowanie funkcji calculateError

//! inny plik
//* testowanie operatorów porównania
//* testowanie konstruktora kopiującego

}
