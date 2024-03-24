#pragma once

#include <string>
#include <unordered_map>

#include "../SimplexPoint.hpp"
#include "../SimplexFigure.hpp"
#include "SimplexCreatorSetting.hpp"

namespace NumericStorm
{
namespace Fitting
{
template<size_t figure_size>
class ISimplexFactory
{
public:
	ISimplexFactory(SimplexCreatorSettings settings)
		:m_settings(settings) {};
	SimplexFigure<figure_size> operator ()(SimplexPoint<figure_size - 1> basedPoint)override = 0;
	void updateSettings(SimplexCreatorSettings newSettings);
private:
	SimplexCreatorSettings m_settings;
};

template<size_t figure_size>
void ISimplexFactory<figure_size>::updateSettings(SimplexCreatorSettings newSettings)
{
	m_settings = newSettings;
};
//TODO implement basic Creator of simplex as base point +/- some epsilon
//TODO implement basic Creator of simplex as random points between bounds
}
}
