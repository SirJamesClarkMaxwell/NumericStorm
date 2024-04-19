#pragma once

#include <array>

#include "IFigureCreator.hpp"
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"


namespace NumericStorm::Fitting {
template <size_t parameter_size>
class BasicSimplexCreator : public IFigureCreator<parameter_size>
{
public:
	BasicSimplexCreator() = default;
	BasicSimplexCreator(const BasicSimplexCreator<parameter_size>&) = default;
	BasicSimplexCreator(BasicSimplexCreator<parameter_size>&&) = default;
	BasicSimplexCreator<parameter_size>& operator=(const BasicSimplexCreator<parameter_size>&) = default;
	BasicSimplexCreator<parameter_size>& operator=(BasicSimplexCreator<parameter_size>&&) = default;

	virtual ~BasicSimplexCreator() = default;

	BasicSimplexCreator(const SimplexCreatorSettigns& settings)
		: IFigureCreator<parameter_size>{ settings } {}


	virtual SimplexFigure<parameter_size> operator()(const SimplexPoint<parameter_size>& point) override {
		std::array<SimplexPoint<parameter_size>, parameter_size + 1> points{};
		points.fill(point);

		for (int i = 1; i < parameter_size + 1; i++) {
			points[i][i] += this->getSettings().getMu();
		}

		SimplexFigure<parameter_size> figure{ points };

		return figure;
	}
};
}