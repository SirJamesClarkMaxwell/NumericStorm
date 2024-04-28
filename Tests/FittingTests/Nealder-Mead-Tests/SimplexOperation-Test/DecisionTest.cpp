#pragma once
#include "../pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;


class ExposedSimplexPoint : public SimplexPoint<4> {
public:
	void setError(double error) {
		this->m_error = error;
	}
};


struct DecisionTest : public ::testing::Test 
{
	DecisionTest() {
		std::vector<CreatorSetUpInfo<StrategySettings>> setup{ {"decide", StrategySettings{}} };
		strategyManager.registerCreators<BasicSimplexDecision<4>>(setup);
	}

	
	StrategyManager<4> strategyManager{};
	ExposedSimplexPoint testedPoint{};
	SimplexFigure<4> testedFigure{};
	
};




//reflectionAccepted
TEST_F(DecisionTest, reflectionAccepted)
{
	SimplexIntermediatePoints<4> interim{ testedFigure, PIndices::PointCount };

	//best <= reflected && reflected < secondWorst

	testedPoint.setError(1.0);
	interim.m_simplexFigure[SimplexFigure<4>::bestPoint] = testedPoint;
	testedPoint.setError(2.0);
	interim[Reflected] = testedPoint;
	testedPoint.setError(3.0);
	interim.m_simplexFigure[secondWorstPoint] = testedPoint;

	EXPECT_FALSE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "reflection");


};



//expansionAcceptedExpanded
TEST_F(DecisionTest, expansionAcceptedExpanded)
{
	SimplexIntermediatePoints<4> interim{ testedFigure, PIndices::PointCount };

	//reflected < best

	testedPoint.setError(2.0);
	interim.m_simplexFigure[SimplexFigure<4>::bestPoint] = testedPoint;
	testedPoint.setError(1.0);
	interim[Reflected] = testedPoint;

	EXPECT_TRUE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "expansion");

	testedPoint.setError(1.0);
	interim[Expanded] = testedPoint;
	testedPoint.setError(2.0);
	interim[Reflected] = testedPoint;



	EXPECT_FALSE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "reflection");


};








//expansionAcceptedReflected
TEST_F(DecisionTest, expansionAcceptedReflected)
{
	SimplexIntermediatePoints<4> interim{ testedFigure, PIndices::PointCount };

	//reflected < best

	testedPoint.setError(2.0);
	interim.m_simplexFigure[SimplexFigure<4>::bestPoint] = testedPoint;
	testedPoint.setError(1.0);
	interim[Reflected] = testedPoint;

	EXPECT_TRUE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "expansion");

	testedPoint.setError(2.0);
	interim[Expanded] = testedPoint;
	testedPoint.setError(1.0);
	interim[Reflected] = testedPoint;

	EXPECT_FALSE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "reflection");


};










//contractionAccepted
TEST_F(DecisionTest, contractionAccepted)
{
	SimplexIntermediatePoints<4> interim{ testedFigure, PIndices::PointCount };

	//reflected >= best

	testedPoint.setError(1.0);
	interim.m_simplexFigure[SimplexFigure<4>::bestPoint] = testedPoint;
	testedPoint.setError(2.0);
	interim[Reflected] = testedPoint;

	EXPECT_TRUE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "contraction");

	testedPoint.setError(1.0);
	interim[Contracted] = testedPoint;
	testedPoint.setError(2.0);
	interim[Reflected] = testedPoint;

	EXPECT_FALSE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "reflection");


};






//shrinking
TEST_F(DecisionTest, shrinkingAccepted)
{
	SimplexIntermediatePoints<4> interim{ testedFigure, PIndices::PointCount };

	//reflected >= best

	testedPoint.setError(1.0);
	interim.m_simplexFigure[SimplexFigure<4>::bestPoint] = testedPoint;
	testedPoint.setError(2.0);
	interim[Reflected] = testedPoint;

	EXPECT_TRUE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "contraction");

	testedPoint.setError(2.0);
	interim[Contracted] = testedPoint;
	testedPoint.setError(1.0);
	interim[Reflected] = testedPoint;

	EXPECT_TRUE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "shrinking");

	EXPECT_FALSE(strategyManager.invoke("decide", interim));
	EXPECT_TRUE(interim.m_currentOperation == "reflection");


};





