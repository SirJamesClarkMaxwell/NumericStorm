#include "pch.h"
#include "SetUpForOperation.hpp"
using namespace NumericStorm::Fitting;
namespace TestingSimpleOperations
{

struct TestingOperations : public testing::Test, public SetUpForOperations
{
	SimplexOperationSettings reflectionSimplexOperationSettings{ 0.5 };
	SimplexOperationSettings expansionSimplexOperationSettings{ 2 };
	Reflection<4>  reflectionMaker{ reflectionSimplexOperationSettings };
	SimplexFigure<4> reflectedFigure;
	void setUp()
	{
		reflectedFigure = reflectionMaker(basicSimplexFigure);
		reflectedFigure.getCentroid().calculateError(referencedData);
		reflectedFigure[0].calculateError(referencedData);
		//reflectedFigure[0].calculateError(referencedData);
		std::cout << "Centroid: " << reflectedFigure.getCentroid()[0] << std::endl;
		std::cout << "Reflected: " << reflectedFigure[0][0] << std::endl;

	}
};

TEST_F(TestingOperations, testingReflection)
{
	double number = 2.71235;
	std::array<double, 4> trueReflectedPointParameters{ number, number, number, number };
	SimplexFigure<4> testedReflectedFigure = reflectionMaker(basicSimplexFigure);
	std::array<double, 4> testedReflectedPointParameters = testedReflectedFigure[0].getParameters();
	for (int i = 0; i < 4;i++)
		EXPECT_NEAR(trueReflectedPointParameters[i], testedReflectedPointParameters[i], 0.001);
};

TEST_F(TestingOperations, TestingExpansion)
{
	setUp();
	double number = 3.25;
	std::array<double, 4> trueExpandedParameters; trueExpandedParameters.fill(number);
	Expansion<4> expansionMaker(expansionSimplexOperationSettings);
	SimplexFigure<4> expandedSimplexFigure = expansionMaker(reflectedFigure);
	expandedSimplexFigure[0].calculateError(referencedData);
	std::array<double, 4> testedExpandedPoint = expandedSimplexFigure[0].getParameters();
	for (int i = 0; i < 4;i++)
		EXPECT_NEAR(trueExpandedParameters[i], testedExpandedPoint[i], 0.001);


};

TEST_F(TestingOperations, TestingContraction)
{
	setUp();
	double number = 1.6375;
	std::array<double, 4> trueContractedParameters; trueContractedParameters.fill(number);
	SimplexOperationSettings contractionSimplexOperationSettings{ 0.5 };
	Contraction<4> contractionMaker(contractionSimplexOperationSettings);
	SimplexFigure<4> contractedSimplexFigure = contractionMaker(reflectedFigure);
	std::array<double, 4> testedContractedPoint = contractedSimplexFigure[0].getParameters();
	for (int i = 0; i < 4;i++)
		EXPECT_NEAR(testedContractedPoint[i], trueContractedParameters[i], 0.001);
};
TEST_F(TestingOperations, TestingShrinking)
{
	setUp();
	std::array<double, 4> initialValues = { 1.9062,1.6000,1.5500,1.2000 };
	std::array<std::array<double, 4>, 4> trueShrinkedParameters;
	for (int i = 0; i < initialValues.size(); ++i)
		trueShrinkedParameters[i].fill(initialValues[i]);


	SimplexOperationSettings shrinkingSimplexOperationSettings{ 0.5 };
	Shrinking<4> shrinkingMaker(shrinkingSimplexOperationSettings);
	SimplexFigure<4> shrinkedSimplexFigure = shrinkingMaker(reflectedFigure);
	for (int i = 0; i < 4; i++)
	{
		std::array<double, 4> testedShrinkedPoint = shrinkedSimplexFigure[i].getParameters();

		for (int j = 0; j < 4; j++)
			EXPECT_NEAR(testedShrinkedPoint[j], trueShrinkedParameters[i][j], 0.001);

	};
};
}