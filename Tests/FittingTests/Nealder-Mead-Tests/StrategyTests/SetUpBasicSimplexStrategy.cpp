#include "SetUpBasicSimplexStrategy.hpp"


void BasicSimplexStrategyTest::SetUp()
{

	gaussianModel = std::make_shared<GaussianModel>();
	chi2ErrorModel = std::make_shared<Chi2ErrorModel>();

	Parameters<4> parameters{ std::array<double, 4>{7, 1, 1, 1} };
	referencedPoint = SimplexPoint<4>(arguments, parameters, additionalParameters);
	referencedPoint.setUp(gaussianModel, chi2ErrorModel);
	referencedData = referencedPoint.calculateData();

	for (int i = 0; i < 5; i++)
	{
		std::array<SimplexPoint<4>, 5> pointsToSimplexFigure;
		double expectedValue = expectedValuesOfGaussian[i];
		std::array<double, 4> SimplexPointToSimplexPointIntoFigure{ expectedValue, 1.1, 1.3, 2 };
		SimplexPoint<4> point{ arguments, Parameters<4>{SimplexPointToSimplexPointIntoFigure}, additionalParameters };
		pointsToSimplexFigure[0] = point;

		//setting other points of simplexFigure
		double epsilon = 0.1;
		for (int j = 1;j < 5;j++)
		{
			std::array<double, 4> arrayToSimplexPoint{ 1 + epsilon, 1.1 + epsilon, 1.3 + epsilon, 2 + epsilon };
			SimplexPoint<4> point{ arguments, Parameters<4>(arrayToSimplexPoint), additionalParameters };
			pointsToSimplexFigure[j] = point;
			epsilon += 0.1;
		}

		// setting models, and calculating errors
		for (auto& point : pointsToSimplexFigure)
		{
			point.setUp(gaussianModel, chi2ErrorModel);
			point.calculateError(referencedData);
		}

		// setting simplexFigure
		SimplexFigure<4> simplexFigure = SimplexFigure<4>(pointsToSimplexFigure, referencedData);
		simplexFigure.sort();
		figures.push_back(simplexFigure);
	}

	std::cout << "I setted up all figures" << std::endl;
}
