# pragma once
#include "SetUpForOperation.hpp"

SetUpForOperations::SetUpForOperations()
{

	gaussianModel = std::make_shared<GaussianModel>();
	chi2ErrorModel = std::make_shared<Chi2ErrorModel>();

	Parameters<4> parameters{ std::array<double, 4>{1, 1, 1, 1} };
	referencedPoint = SimplexPoint<4>(arguments, parameters, additionalParameters);
	referencedPoint.setUp(gaussianModel, chi2ErrorModel);
	referencedData = referencedPoint.calculateData();

	std::array<SimplexPoint<4>, 5> pointsToSimplexFigure;
	for (int i = 0; i < 5; i++)
	{
		double number = numbersToSimplexFigure[i];
		std::array<double, 4> arrayToSimplexPoint{ number,number,number,number };
		pointsToSimplexFigure[i] = SimplexPoint<4>(arguments, Parameters<4>(arrayToSimplexPoint), additionalParameters);
		pointsToSimplexFigure[i].setUp(gaussianModel, chi2ErrorModel);
		pointsToSimplexFigure[i].calculateError(referencedData);
	}

	basicSimplexFigure = SimplexFigure<4>(pointsToSimplexFigure);
	basicSimplexFigure.sort();

}

