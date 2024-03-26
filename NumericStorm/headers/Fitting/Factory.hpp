#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "./Fitting/Exceptions/NoAvailableFactoryException.hpp"
#include "CreatorInterface.hpp"

namespace NumericStorm {
namespace Fitting {
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

	virtual void registerCreator(const std::string& creatorName, const Creator& instance);
	virtual void deleteCreator(const std::string& creatorName) throw (NoAvailableFactoryException);
	virtual typename Creator::Out invoke(const std::string& creatorName, const typename Creator::In& input) throw (NoAvailableFactoryException);
	virtual void updateSettings(const std::string& creatorName, const typename Creator::Settings& settings) throw (NoAvailableFactoryException);
protected:
	std::unordered_map<std::string, std::unique_ptr<Creator>> m_creatorList{};

private:
	bool checkIfAvailable(const std::string& creatorName) const {
		return m_creatorList.find(creatorName) != m_creatorList.end();
	}
};
template<class Creator>
void Factory<Creator>::registerCreator(const std::string& creatorName, const Creator& instance) {
	m_creatorList[creatorName] = std::make_unique<Creator>(instance);
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
void Factory<Creator>::updateSettings(const std::string& creatorName, const typename Creator::Settings& settings) {
	auto simplexCreator = m_creatorList.find(creatorName);

	if (checkIfAvailable(creatorName))
		return m_creatorList[creatorName]->get()->updateSettings(settings);

	throw NoAvailableFactoryException(creatorName);
};


}
}