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
	ISimplexFactory(SimplexCreatorSettigns settings) 
	:m_settings(settings){};
	SimplexFigure<figure_size> operator ()(SimplexPoint<figure_size-1> basedPoint)override = 0;
	void updateSettings(SimplexCreatorSettigns newSettigns);
private:
	SimplexCreatorSettigns m_settings;
};

template<size_t figure_size>
void ISimplexFactory<figure_size>::updateSettings(SimplexCreatorSettigns newSettigns)
	{m_settings = newSettigns;};
}
}
