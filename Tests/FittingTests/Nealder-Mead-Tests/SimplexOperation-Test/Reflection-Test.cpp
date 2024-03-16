#include "pch.h"
#include "SetUpForOperation.hpp"
using namespace NumericStorm::Fitting;
namespace TestingSimpleOperations
{

struct TestingOperations : public testing::Test, public SetUpForOperations
{};

TEST_F(TestingOperations, testingReflection)
{


	SimplexOperationSettings simplexOperationSettings(0.5);
	Reflection<4>  reflectionMaker(simplexOperationSettings);
	SimplexFigure<4> testedReflectedFigure = reflectionMaker(basicSimplexFigure);
	double number = 2.71235;
	std::array <double, 4> trueReflectedPointParameters{ number, number, number, number };
	std::array<double, 4> testedReflectedPointParameters = testedReflectedFigure[0].getParameters();
	for (int i = 0; i < 4;i++)

		EXPECT_NEAR(trueReflectedPointParameters[i], testedReflectedPointParameters[i], 0.001);

};
}