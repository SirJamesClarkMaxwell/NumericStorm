#include "FittingTestsSetUp.hpp"



using namespace NumericStorm::Fitting;

namespace TestingModel
{

struct TestingGaussianModel :public ::testing::Test
{
	UsefulObjects objs{};
};

TEST_F(TestingGaussianModel, TestingSimpleGaussianModel)
{
	for (int i = 0; i < objs.arguments.size(); i++)
		EXPECT_NEAR(objs.true_datum[1][i], objs.trueValues[i], 0.001);
};
}