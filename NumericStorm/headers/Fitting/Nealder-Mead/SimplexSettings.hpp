#pragma once
#include <memory>

#include "../FitterSettings.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
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
	template<class SettingsType>
	using CreatorInfoVector = std::vector<CreatorSetUpInfo<StrategyManager>>;
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
	CreatorInfoVector<SimplexCreatorSettings> m_simplexCreatorSetUpInfo;
	CreatorInfoVector<SimplexOperationSettings> m_simplexOperationSetUpInfo;
	CreatorInfoVector<StrategySettings> m_simplexStrategySetUpInfo;
protected:
	template <class Creator>
	void registerOperations(Factory<Creator::parent>& factory, int pos, const std::vector<Creator::SetUpInfo>& info_vec) {

	}
	template <class Factory, class Creator>
	void registerOperations(Factory<Creator::parent>& factory, int pos, const std::vector<CreatorSetUpInfo<Creator::Settings>>& info_vec) {
		registerOneCreator(factory, info_vec[pos]);
	}

	template <class Factory, class Creator, class... CreatorTypes>
	void registerOperations(Factory<Creator::parent>& factory, int pos, const std::vector<CreatorSetUpInfo<Creator::Settings>>& info_vec) {
		registerOneCreator(factory, info_vec[pos]);
		if (pos >= info_vec.size()) return;
		registerOperations<Factory, CreatorTypes...>(factory, pos + 1, info_vec);
	}

	template <class Creator>
	void registerOneCreator(Factory<Creator::parent>& factory, const CreatorSetUpInfo<Creator::Settings>& creatorSetUpInfo) {
		Creator cr(creatorSetUpInfo.settings);
		factory.registerCreator(creatorSetUpInfo.name, cr);
	}

	SimplexOperationFactory<ISimplexOperation<parameter_size>> fac;
	std::vector<CreatorSetUpInfo<ISimplexOperation::Settings>> info;

	registerOperations(fac, 0, info);
};
}
}