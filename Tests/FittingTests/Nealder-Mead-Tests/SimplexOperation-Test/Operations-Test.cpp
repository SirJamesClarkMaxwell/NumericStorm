#include "../pch.h"
#include "FittingTestsSetup.hpp"
#include <functional>
using namespace NumericStorm::Fitting;
namespace TestingSimpleOperations
{

struct TestingOperations : public testing::Test
{
	
	void setUp()
	{
		std::shared_ptr<Data> data_ptr = std::make_shared<Data>(objs.true_datum);

		referenceFigure[0] = SimplexPoint<4>{ data_ptr, objs.evaluatedArray };

		referenceFigure[0].onEvaluate([&](SimplexPoint<4>& point) {
			point.evaluatePoint(objs.gModel, objs.eModel, objs.additionalParameters);
		});

		referenceFigure[0].evaluatePoint();
		for (int i = 1; i < 5; i++) {
			referenceFigure[i] = SimplexPoint<4>{ referenceFigure[0] };
			referenceFigure[i][i - 1] += 1;
			referenceFigure[i].evaluatePoint();
		}
		referenceFigure.sort();

		testedFigure = referenceFigure;

	}

	UsefulObjects objs{};
	SimplexFigure<4> testedFigure{};
	SimplexFigure<4> referenceFigure{};

	Reflection<4> reflOp{ 1.5 };
	Expansion<4> expOp{ 0.5 };
	Contraction<4> contOp{ 2.0 };
	Shrinking<4> shOp{ 0.5 };
};

TEST_F(TestingOperations, testingReflection)
{
	setUp();
	
	SimplexIntermediatePoints<4> interim{ referenceFigure, PIndices::PointCount };

	double alpha = reflOp.getSettings().getFactor();
	const SimplexPoint<4>& centroid = interim.m_simplexFigure.getCentroid();
	SimplexPoint<4>& reflectedPoint = interim.m_intermediatePoints[Reflected];
	const SimplexPoint<4>& wPoint = interim.m_simplexFigure[worstPoint];

	auto difference = centroid - wPoint;
	auto scaled = difference * alpha;
	reflectedPoint = centroid + scaled;

	reflectedPoint.evaluatePoint();

	SimplexIntermediatePoints<4> tinterim{ testedFigure, PIndices::PointCount };
	reflOp(tinterim);
	tinterim.m_intermediatePoints[PIndices::Reflected].evaluatePoint();

	EXPECT_NEAR(reflectedPoint.getError(), tinterim.m_intermediatePoints[PIndices::Reflected].getError(), 0.01);
	for (int i = 0; i < 4; i++) {
		//[1.0, -0.9999999999999998, 1.0, 1.1102230246251565e-16] - parameters of reflected point computed manually by python script
		std::cout << reflectedPoint[i] << std::endl;
		EXPECT_NEAR(reflectedPoint[i], tinterim.m_intermediatePoints[PIndices::Reflected][i], 0.01);
	}

	
};
TEST_F(TestingOperations, TestingExpansion)
{
	setUp();
	SimplexIntermediatePoints<4> interim{ referenceFigure, PIndices::PointCount };

	const SimplexPoint<4>& centroid = interim.m_simplexFigure.getCentroid();
	SimplexPoint<4>& expanded = interim[PIndices::Expanded];
	const SimplexPoint<4>& reflected = interim[PIndices::Reflected];
	double gamma = expOp.getSettings().getFactor();

	auto difference = reflected - centroid;
	auto scaled = difference * gamma;
	expanded = centroid + scaled;

	expanded.evaluatePoint();

	SimplexIntermediatePoints<4> tinterim{ testedFigure, PIndices::PointCount };
	expOp(tinterim);
	tinterim.m_intermediatePoints[PIndices::Expanded].evaluatePoint();

	EXPECT_NEAR(expanded.getError(), tinterim.m_intermediatePoints[PIndices::Expanded].getError(), 0.01);
	for (int i = 0; i < 4; i++) {
		std::cout << expanded[i] << std::endl;
		EXPECT_NEAR(expanded[i], tinterim.m_intermediatePoints[PIndices::Expanded][i], 0.01);
	}
};

TEST_F(TestingOperations, TestingContraction)
{
	setUp();

};
TEST_F(TestingOperations, TestingShrinking)
{
	setUp();

};
}