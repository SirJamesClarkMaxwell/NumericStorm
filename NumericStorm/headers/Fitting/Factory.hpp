#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "./Fitting/Exceptions/NoAvailableFactoryException.hpp"
#include "CreatorInterface.hpp"

namespace NumericStorm {
namespace Fitting {
template<class SettingType>
struct CreatorSetUpInfo
{
	std::string name;
	SettingType settings;
};
template<class Creator>
class Factory {

	static_assert(std::derived_from<Creator, CreatorInterface> == true);
public:
	Factory() = default;
	Factory(const Factory<Creator>&) = default;
	Factory(Factory<Creator>&&) = default;
	Factory<Creator>& operator=(const Factory<Creator>&) = default;
	Factory<Creator>& operator=(Factory<Creator>&&) = default;

	virtual ~Factory() = default;

	virtual void deleteCreator(const std::string& creatorName);
	virtual typename Creator::Out invoke(const std::string& creatorName, const typename Creator::In& input);
	virtual void updateSettings(const CreatorSetUpInfo<typename Creator::Settings>& newSettings);
	template <class... CreatorTypes>
	virtual void registerCreators(const std::vector<CreatorSetUpInfo<typename Creator::Settings>>& settingsVector)
	{
		registerCreators<CreatorTypes...>(0, settingsVector);
	};


protected:
	std::unordered_map<std::string, std::unique_ptr<Creator>> m_creatorList{};

private:

	template<class CurrentCreator, class NextCreator, class ...RestCreators>
	void registerCreators(int position, std::vector<CreatorSetUpInfo<typename Creator::Settings>>& settingsVector)
	{
		if (position >= settingsVector.size())
			return;
		registerOneCreator<CurrentCreator>(settingsVector[position]);
		registerCreators<NextCreator, RestCreators...>(position + 1, settingsVector);

	};
	template<class NextCreator>
	void registerCreators(int position, std::vector<typename Creator::Settings >> settingsVector)
	{
		if (position >= settingsVector.size())
			return;
		registerOneCreator<NextCreator>(settingsVector[position]);

	};
	bool checkIfAvailable(const std::string& creatorName) const
	{
		return m_creatorList.find(creatorName) != m_creatorList.end();
	}
	void registerCreator(const std::string& creatorName, const Creator& instance)
	{
		m_creatorList[creatorName] = std::make_unique<Creator>(instance);
	};;
	template<class DerivedCreator>
	void registerOneCreator(const CreatorSetUpInfo<typename Creator::Settings>& creatorSetUpInfo)
	{
		static_assert(std::derived_from<DerivedCreator, Creator> == true);
		DerivedCreator creator(creatorSetUpInfo.settings);
		factory.registerCreator(creatorSetUpInfo.name, creator);
	};
};


template<class Creator>
void Factory<Creator>::deleteCreator(const std::string& creatorName) {
	if (checkIfAvailable(creatorName))
		m_creatorList.erase(creatorName);
	else
		throw NoAvailableFactoryException(creatorName);
};
template<class Creator>
typename Creator::Out Factory<Creator>::invoke(const std::string& creatorName, const typename Creator::In& input) {
	if (checkIfAvailable(creatorName))
		return m_creatorList[creatorName]->get()->operator()(input);

	throw NoAvailableFactoryException(creatorName);
};
template<class Creator>
void Factory<Creator>::updateSettings(const CreatorSetUpInfo<typename Creator::Settings>& newSettings) {
	std::string creatorName = newSettings.name;
	auto simplexCreator = m_creatorList.find(creatorName);

	if (checkIfAvailable(creatorName))
		return m_creatorList[creatorName]->get()->updateSettings(newSettings.settings);

	throw NoAvailableFactoryException(creatorName);
};


}
}