#pragma once

#include <variant>
#include <initializer_list>

#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
#include "SimplexCreatorSettings.hpp"
#include "CreatorInterface.hpp"
#include "IFigureCreator.hpp"


namespace NumericStorm::Fitting {

//todo change this name to something better
//PROPOSAL Change name to CreatorConditions
template<size_t parameter_size>
struct CreatorInput
{
public:
	explicit CreatorInput(const SimplexPoint<parameter_size>& point, const Parameters<parameter_size>& min, const Parameters<parameter_size>& max)
		: initialPoint{ point }, minBounds{ min }, maxBounds{ max } {};
	SimplexPoint<parameter_size> initialPoint;
	Parameters<parameter_size> minBounds;
	Parameters<parameter_size> maxBounds;

};
template<size_t parameter_size>
class IFigureCreator : public CreatorInterface<const CreatorInput<parameter_size>&, SimplexFigure<parameter_size>, SimplexCreatorSettings>
{
public:
	using InterfaceType = typename CreatorInterface<const CreatorInput<parameter_size>&, SimplexFigure<parameter_size>, SimplexCreatorSettings>;
	using In = typename InterfaceType::In;
	using Out = typename InterfaceType::Out;
	using Settings = typename InterfaceType::Settings;

	//todo same story with default constructor in InterfaceType
	explicit IFigureCreator(const SimplexCreatorSettings& settings)
		: CreatorInterface<In, Out, Settings>{} { this->m_settings = settings; }
	virtual ~IFigureCreator() = default;
};
}