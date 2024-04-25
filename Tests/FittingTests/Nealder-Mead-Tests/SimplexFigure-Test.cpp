#pragma once
#include <iostream>
#include "..\FittingTestsSetUp.hpp"
namespace TestingSimplexFigure
{

using namespace NumericStorm::Fitting;
struct TestingSimplexFigure : public::testing::Test
{
	TestingSimplexFigure() {
		std::shared_ptr<Data> data_ptr = std::make_shared<Data>(objs.true_datum);
		pointsForFigure[0] = SimplexPoint<4>{data_ptr, objs.evaluatedArray};
		pointsForFigure[0].evaluatePoint(objs.gModel, objs.eModel, objs.additionalParameters);
		for (int i = 1; i < 5; i++) {
			pointsForFigure[i] = SimplexPoint<4>{ data_ptr, objs.evaluatedArray };
			pointsForFigure[i][i - 1] += 1;
			pointsForFigure[i].evaluatePoint(objs.gModel, objs.eModel, objs.additionalParameters);
		}

		testedFigure = SimplexFigure<4>{ pointsForFigure };

		std::sort(pointsForFigure.begin(), pointsForFigure.end());
		std::reverse(pointsForFigure.begin(), pointsForFigure.end());

		

		for (int i = 1; i < 5; i++) {
			manualCentroid += pointsForFigure[i];
		}

		manualCentroid /= 5;
	}
	UsefulObjects objs{};

	SimplexFigure<4> testedFigure{};
	SimplexPoint<4> manualCentroid{};
	std::array<SimplexPoint<4>, 5> pointsForFigure{};
};

TEST_F(TestingSimplexFigure, testingSortingSimplexFigure)
{
	testedFigure.sort();
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 4; k++) {
			EXPECT_NEAR(testedFigure[i][k], pointsForFigure[i][k], 0.01);
		}
	}
};

TEST_F(TestingSimplexFigure, testingCalculatingCentroid)
{
	const SimplexPoint<4>& centr = testedFigure.getCentroid();
	for (int i = 0; i < 4; i++) {
		EXPECT_NEAR(centr[i], manualCentroid[i], 0.01);
	}
};


}