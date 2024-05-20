#pragma once

#include <array>

#include "IFigureCreator.hpp"
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
#include "SimplexCreatorSettings.hpp"
#include "Random.hpp"


namespace NumericStorm::Fitting {
template <size_t parameter_size>
class BasicSimplexCreator : public IFigureCreator<parameter_size>
{
public:
	//using Random;
	explicit BasicSimplexCreator(const SimplexCreatorSettings& settings)
		: IFigureCreator<parameter_size>{ settings } {}
	/*
	BasicSimplexCreator(const BasicSimplexCreator<parameter_size>&) = default;
	BasicSimplexCreator(BasicSimplexCreator<parameter_size>&&) = default;
	BasicSimplexCreator<parameter_size>& operator=(const BasicSimplexCreator<parameter_size>&) = default;
	BasicSimplexCreator<parameter_size>& operator=(BasicSimplexCreator<parameter_size>&&) = default;
	*/

	virtual ~BasicSimplexCreator() = default;

	//todo modify this to be more abstract, in terns of generating sets of random SimplexPoints
	virtual SimplexFigure<parameter_size> operator()(const CreatorInput<parameter_size>& input) override {
		std::array<SimplexPoint<parameter_size>, parameter_size + 1> points{};
		points.fill(input.initialPoint);

		for (int i = 1; i < parameter_size + 1; i++)
			for (int j = 1; j < parameter_size; j++)
				points[i][j] += Random::Float(input.minBounds[j], input.maxBounds[j]);

		SimplexFigure<parameter_size> figure{ points };
		return figure;
	}
};
}