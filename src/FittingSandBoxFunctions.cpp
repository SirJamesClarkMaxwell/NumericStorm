#pragma once
#include "../headers/FittingSandBoxFunctions.hpp"

using namespace NumericStorm::Fitting;


void GaussianModel::gaussianFunction(Data& datum, const Parameters<3>& parameters, const AdditionalParameters& additionalParameters)
{
	const auto& [A, sigma, c] = parameters.getParameters();
	for (size_t i = 0; i < datum[0].size(); i++)
	{
		double updatedX = (datum[0][i] - 1);
		datum[1][i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
	}
}

double Chi2ErrorModel::chi2ErrorModelFunction(const Data& referenceData, const Data& evaluatedData) {
	const auto& referenceValues = referenceData[1];
	const auto& evaluatedValues = evaluatedData[1];
	double chi2 = 0;

	for (size_t i = 0; i < referenceValues.size(); i++)
	{
		chi2 += pow(referenceValues[i] - evaluatedValues[i], 2);
	}

	return chi2;
}


void BasicAdapter::setUp(typename BasicAdapter::Input& input)
{
	static SimplexPoint<3> point{};

	auto& saState = input.getWrappedState();

	point = input.getWrappedState().getSimplexFigure().getPoints()[0];

	input.setCallback([&](const std::vector<double>& config) -> double {
		std::copy(config.cbegin(), config.cend(), point.getParameters().begin());
		point.evaluatePoint();
		return point.getError();
		});

	input.getEnergies().resize(saState.getSimplexFigure().getPoints().size());

	input.getConfigurations().resize(saState.getSimplexFigure().getPoints().size());

	for (auto& config : input.getConfigurations()) {
		config.resize(saState.getSimplexFigure().getPoints().size() - 1);
	}
}

void BasicAdapter::update(typename BasicAdapter::Input& input)
{
	auto& saState = input.getWrappedState();
	auto& simplex = saState.getSimplexFigure();

	for(size_t i = 0; i < simplex.getPoints().size(); i++)
	{
		auto& point = simplex.getPoints()[i];
		input.getEnergies()[i] = &point.getError();

		for (size_t k = 0; k < simplex.getPoints().size() - 1; k++) {
			input.getConfigurations()[i][k] = &point.getParameters()[k];
		}
		
	}
}
