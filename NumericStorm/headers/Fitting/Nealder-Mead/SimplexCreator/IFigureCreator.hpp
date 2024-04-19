#pragma once


#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
#include "SimplexCreatorSettings.hpp"
#include "CreatorInterface.hpp"
#include "IFigureCreator.hpp"

namespace NumericStorm::Fitting {

template<size_t parameter_size>
class IFigureCreator : public CreatorInterface<const SimplexPoint<parameter_size>&, SimplexFigure<parameter_size>, SimplexCreatorSettings>
{
public:
	using InterfaceType = typename CreatorInterface<SimplexFigure<parameter_size>&, SimplexFigure<parameter_size>&, SimplexOperationSettings>;
	using In = typename InterfaceType::In;
	using Out = typename InterfaceType::Out;
	using Settings = typename InterfaceType::Settings;

	IFigureCreator() = default;
	IFigureCreator(const IFigureCreator<parameter_size>&) = default;
	IFigureCreator(IFigureCreator<parameter_size>&&) = default;
	IFigureCreator<parameter_size>& operator=(const IFigureCreator<parameter_size>&) = default;
	IFigureCreator<parameter_size>& operator=(IFigureCreator<parameter_size>&&) = default;

	virtual ~IFigureCreator() = default;

	//todo same story with default constructor in InterfaceType
	IFigureCreator(const SimplexCreatorSettings& settings)
		: CreatorInterface<In, Out, Settings>{} {
			this->m_settings = settings;
		}

};
}