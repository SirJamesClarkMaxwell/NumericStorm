#pragma once

#include <variant>
#include <initializer_list>

#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
#include "SimplexCreatorSettings.hpp"
#include "CreatorInterface.hpp"
#include "IFigureCreator.hpp"

namespace NumericStorm::Fitting {
class Random
{
public:
	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	static uint32_t UInt()
	{
		return s_Distribution(s_RandomEngine);
	}

	static uint32_t UInt(uint32_t min, uint32_t max)
	{
		return min + (s_Distribution(s_RandomEngine) % (max - min + 1));
	}

	static float Float(double min, double max)
	{
		double factor = (max - min) + min;
		return (float)factor * s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}
private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};

//todo change this name to something better
template<size_t parameter_size>
struct CreatorInput
{
public:
	explicit CreatorInput(std::initializer_list<std::variant<SimplexPoint<parameter_size>, double>> arguments)
		//: initialPoint{ std::get<0>(arguments) }, min{ std::get<1>(arguments) }, max{ std::get<2>(arguments) } {}
		: initialPoint{ arguments[0] }, min{ arguments[1] }, max{ arguments[2] } {};
	SimplexPoint<parameter_size> initialPoint;
	double min;
	double max;

};
template<size_t parameter_size>
class IFigureCreator : public CreatorInterface<const CreatorInput<parameter_size>&, SimplexFigure<parameter_size>, SimplexCreatorSettings>
{
public:
	using InterfaceType = typename CreatorInterface<CreatorInput<parameter_size>&, SimplexFigure<parameter_size>&, SimplexOperationSettings>;
	using In = typename InterfaceType::In;
	using Out = typename InterfaceType::Out;
	using Settings = typename InterfaceType::Settings;

	//todo same story with default constructor in InterfaceType
	explicit IFigureCreator(const SimplexCreatorSettings& settings)
		: CreatorInterface<In, Out, Settings>{} { this->m_settings = settings; }
	/*
		IFigureCreator() = default;
		IFigureCreator(const IFigureCreator<parameter_size>&) = default;
		IFigureCreator(IFigureCreator<parameter_size>&&) = default;
		IFigureCreator<parameter_size>& operator=(const IFigureCreator<parameter_size>&) = default;
		IFigureCreator<parameter_size>& operator=(IFigureCreator<parameter_size>&&) = default;
	*/
	virtual ~IFigureCreator() = default;
};
}