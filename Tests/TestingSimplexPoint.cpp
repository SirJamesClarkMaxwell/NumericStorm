#include "pch.h"

using namespace NumericStorm::Fitting;

namespace TestingSimplexPointOperators 
{
	struct SimplexPointOperatorsAddition:public testing::Test {
		AdditionalParameters additionalParameters;

		std::array<double, 4> initialParametersArray{ 2,2,2,2 };
		SimplexPoint<4> initialSimplexPoint{initialParametersArray, additionalParameters};

		std::array<double, 4> stepParametersArray{ 1,1,1,1 };
		SimplexPoint<4> additionSimplexPoint{stepParametersArray , additionalParameters};

		std::array<double, 4> finalParametersArray{ 3,3,3,3 };
		SimplexPoint<4> finalSimplexPoint{ finalParametersArray, additionalParameters };

	};

	TEST_F(SimplexPointOperatorsAddition, SimpleAddition) 
	{
	
		SimplexPoint<4> testedAdditionPoint(initialSimplexPoint);
		testedAdditionPoint = testedAdditionPoint + additionSimplexPoint;

		for (int i = 0; i < 4; i++)
			EXPECT_DOUBLE_EQ(testedAdditionPoint[i], finalSimplexPoint[i]);
	};

	TEST_F(SimplexPointOperatorsAddition, AdditionAssignment)
	{

		SimplexPoint<4> testedAdditionPoint(initialSimplexPoint);
		testedAdditionPoint += additionSimplexPoint;

		for (int i = 0; i < 4; i++)
			EXPECT_DOUBLE_EQ(testedAdditionPoint[i], finalSimplexPoint[i]);
	};

}