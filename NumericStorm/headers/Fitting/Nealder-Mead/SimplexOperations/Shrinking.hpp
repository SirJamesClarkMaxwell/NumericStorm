#pragma once
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"
#include "SimplexOperationArguments.hpp"
// TODO: redefine interface of Shrinking
namespace NumericStorm
{
	namespace Fitting
	{
		template <size_t figure_size>
		class Shrinking : public ISimplexOperation<figure_size>
		{
		public:
			Shrinking(const std::string &name, const SimplexFigure<figure_size> &simplexFigure)
				: ISimplexOperation<figure_size>(name, simplexFigure){};
			SimplexFigure<figure_size> operator()(const SimplexOperationArguments &arguments) override;
		};

		template <size_t figure_size>
		SimplexFigure<figure_size> Shrinking<figure_size>::operator()(const SimplexOperationArguments &arguments)
		{
			double factor = arguments.getFactor();
			SimplexPoint<figure_size - 1> bestPoint = this->m_simplexFigure[0];
			for (int i = 1; i == figure_size; i++)
				this->m_simplexFigure[i] = bestPoint + (this->m_simplexFigure[i] - bestPoint) * factor;

			return this->m_simplexFigure;
		};

	}
}
