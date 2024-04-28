#pragma once
#include "../pch.h"
#include "SetUpOperationFactory.hpp"

namespace TestingSimplexOperationFactory {
//* testing registering Operations
TEST_F(OperationFactoryTest, registeringSimplexOperation)
{

	SimplexIntermediatePoints<4> interim{ referenceFigure, PIndices::PointCount };

	opFactory.invoke("reflection", interim);


	//[1.0, -0.9999999999999998, 1.0, 1.1102230246251565e-16] - parameters of reflected point computed manually by python script
	std::vector<double> manualData{ 1.0, -0.9999999999999998, 1.0, 1.1102230246251565e-16 };

	for (int i = 0; i < 4; i++) {
		
		std::cout << manualData[i] << std::endl;
		EXPECT_NEAR(manualData[i], interim.m_intermediatePoints[PIndices::Reflected][i], 0.01);
	}

};
//* testing unregistering Operations
TEST_F(OperationFactoryTest, unRegisteringSimplexOperation)
{
	
	bool threw = false;

	try {
		opFactory.deleteCreator("reflection");
	}
	catch (NoAvailableFactoryException e) {
		threw = true;
	}

	EXPECT_FALSE(threw);

	try {
		SimplexIntermediatePoints<4> interim{ referenceFigure, PIndices::PointCount };
		opFactory.invoke("reflection", interim);
	}
	catch (NoAvailableFactoryException e) {
		threw = true;
	}

	EXPECT_TRUE(threw);

	try {
		SimplexIntermediatePoints<4> interim{ referenceFigure, PIndices::PointCount };
		opFactory.invoke("noOperation", interim);
	}
	catch (NoAvailableFactoryException e) {
		threw = true;
	}

	EXPECT_TRUE(threw);
};

//* testing updating settings
TEST_F(OperationFactoryTest, updatingSettings)
{
	bool threw = false;
	SimplexIntermediatePoints<4> fPoints{referenceFigure, PIndices::PointCount};
	SimplexIntermediatePoints<4> oPoints{referenceFigure, PIndices::PointCount};

	try {
		opFactory.updateSettings({ "expansion", 0.3 });
		Expansion<4> expOP{ 0.3 };

		opFactory.invoke("expansion", fPoints);
		expOP(oPoints);
	}
	catch (NoAvailableFactoryException e) {
		threw = true;
	}

	EXPECT_FALSE(threw);

	try {
		opFactory.updateSettings({ "noOperation", 0.3 });
	}
	catch (NoAvailableFactoryException e) {
		threw = true;
	}

	EXPECT_TRUE(threw);

	EXPECT_NEAR(fPoints.m_intermediatePoints[PIndices::Expanded].getError(), oPoints.m_intermediatePoints[PIndices::Expanded].getError(), 0.01);

	for (int i = 0; i < 4; i++) {
		EXPECT_NEAR(fPoints.m_intermediatePoints[PIndices::Expanded][i], oPoints.m_intermediatePoints[PIndices::Expanded][i], 0.01);
	}


};

}