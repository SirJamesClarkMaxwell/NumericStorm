#pragma once
#include "pch.h"
#include <iostream>
#include "..\FittingTestsSetUp.hpp"
namespace TestingSimplexFigure
{

using namespace NumericStorm::Fitting;
struct TestingSimplexFigure : public::testing::Test, public UsefullyObjects
{
public:
	TestingSimplexFigure()
	{

		for (int i = 1; i <= 5; i++)
		{
			std::array<double, 4> currentArray = { i,i,i,i };
			SimplexPoint<4> currentPoint = SimplexPoint<4>{ arguments, currentArray, additionalParameters };
			pointsToSimplexFigure[i - 1] = currentPoint;
		}
		double trueCentroidValue = 0;
		for (int i = 1;i <= 5;i++)
			trueCentroidValue += i;
		trueCentroidValue /= 4;
		std::array<double, 4> trueCentroidArray = { trueCentroidValue,trueCentroidValue,trueCentroidValue,trueCentroidValue };
		trueCentroid = SimplexPoint<4>{ arguments,trueCentroidArray , additionalParameters };

	}
	SimplexPoint<4> trueCentroid;
	std::array<SimplexPoint<4>, 5> pointsToSimplexFigure;
};

TEST_F(TestingSimplexFigure, testingCalculatingCentroid)
{
	SimplexFigure<4> testedSimplexFigure{ pointsToSimplexFigure };
	std::array<double, 4> testedCentroidPoint = testedSimplexFigure.getCentroid().getParameters();
	std::array<double, 4> trueCentroidParameters = trueCentroid.getParameters();
	for (int i = 0;i < 4; i++)
	{
		std::cout << testedCentroidPoint[i] << trueCentroidParameters[i] << std::endl;
		EXPECT_NEAR(testedCentroidPoint[i], trueCentroidParameters[i], 0.01);
	}

}

TEST_F(TestingSimplexFigure, testingSortingSimplexFigure)
{
	std::array<double, 5> numbersToSimplexFigure = { 0.1, 2.5, 1.1, 2.1, 2 };
	std::array<SimplexPoint<4>, 5> pointsToSimplexFigureInSortingTest;
	std::array<double, 5> trueErrors;

	for (int i = 0; i < 5;i++)
	{
		auto number = numbersToSimplexFigure[i];
		std::array<double, 4> pointArray = { number,number,number,number };
		SimplexPoint<4> pointToSimplexFigure{ arguments,pointArray,additionalParameters };

		pointToSimplexFigure.setUp(gaussianModel, chi2ErrorModel);
		pointToSimplexFigure.calculateError(referencedData);
		double calculatedError = pointToSimplexFigure.getError();
		trueErrors[i] = Chi2ErrorModel()(referencedData, GaussianModel()(arguments, Parameters{ pointArray }, additionalParameters));
		pointsToSimplexFigureInSortingTest[i] = pointToSimplexFigure;
	}
	SimplexFigure<4> testedSimplexFigureInTestSorting{ pointsToSimplexFigureInSortingTest };
	testedSimplexFigureInTestSorting.sort(false);
	std::sort(trueErrors.begin(), trueErrors.end());

	for (int i = 0; i < 5; i++)
	{
		double testedError = testedSimplexFigureInTestSorting[i].getError();
		double trueError = trueErrors[i];
		EXPECT_NEAR(testedError, trueError, 0.001);
	}


};
}