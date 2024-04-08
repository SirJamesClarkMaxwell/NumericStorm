#pragma once
#include <memory>

#include "../FitterSettings.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
#include "../Exceptions/WrongTemplateArgument.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<class SettingType>
struct CreatorSetUpInfo
{
	std::string name;
	SettingType settings;
};
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class SimplexSettings : public FitterSettings<parameter_size, AuxilaryParameters>
{
public:
	//todo implement builder
	SimplexSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, int maxIteration, double minError)
		: FitterSettings<parameter_size, AuxilaryParameters>(model, errorModel, maxIteration, minError) {}
	SimplexSettings() = delete;
	SimplexSettings(const SimplexSettings<parameter_size, AuxilaryParameters>&) = default;
	SimplexSettings(SimplexSettings<parameter_size, AuxilaryParameters>&&) = default;
	SimplexSettings<parameter_size, AuxilaryParameters>& operator=(const SimplexSettings<parameter_size, AuxilaryParameters>&) = default;
	SimplexSettings<parameter_size, AuxilaryParameters>& operator=(SimplexSettings<parameter_size, AuxilaryParameters>&&) = default;
	virtual ~SimplexSettings() = default;

protected:
	template<class SettingsType>
	using CreatorInfoVector = std::vector<CreatorSetUpInfo<StrategyManager>>;
	CreatorInfoVector<SimplexCreatorSettings> m_simplexCreatorSetUpInfo;
	CreatorInfoVector<SimplexOperationSettings> m_simplexOperationSetUpInfo;
	CreatorInfoVector<StrategySettings> m_simplexStrategySetUpInfo;
protected:

	//NOTE this ParentType must be defined in all class derived from CreatorInterface
	template <class Factory, class Creator, class... CreatorTypes>
	void registerCreators(Factory<Creator::ParentType>& factory, int pos, const std::vector<CreatorSetUpInfo<Creator::Settings>>& info_vec)
	{
		if (info_vec.size() == 0)
			throw WrongTemplateArgument();

		registerOneCreator(factory, info_vec[pos]);
		if (pos >= info_vec.size())
			return;
		registerCreators<Factory, CreatorTypes...>(factory, pos + 1, info_vec);
	}

	template <class Creator>
	void registerOneCreator(Factory<Creator::ParentType>& factory, const CreatorSetUpInfo<Creator::Settings>& creatorSetUpInfo)
	{
		Creator cr(creatorSetUpInfo.settings);
		factory.registerCreator(creatorSetUpInfo.name, cr);
	}

	template <class Factory, class Creator>
	void registerCreators(Factory<Creator::ParentType>& factory, int pos, const std::vector<CreatorSetUpInfo<Creator::Settings>>& info_vec)
	{
		if (pos >= info_vec.size())
			return;
		registerOneCreator(factory, info_vec[pos]);
	}
	/*
	template <class Creator>
	void registerCreators(Factory<Creator::ParentType>& factory, int pos, const std::vector<Creator::SetUpInfo>& info_vec)
	{
		//NOTE If we are using exception we don't have to use this method
	}
	*/
};
}
}