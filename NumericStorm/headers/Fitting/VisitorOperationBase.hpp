#pragma once

#include "OperationSettings.hpp"

namespace NumericStorm::Fitting {
using namespace NumericStorm::Concepts;

	template<OperationSettings Settings>
	class VisitorOperationBase
	{
	public:
		using SettingsT = Settings;
	
		VisitorOperationBase(const SettingsT& settings)
			: m_settings(settings) {}
	
		void updateSettings(const SettingsT& settings)
		{
			m_settings = settings;
		}
	
		const SettingsT& getSettings() const
		{
			return m_settings;
		}
	
		virtual ~VisitorOperationBase() = default;
	
	protected:
		SettingsT m_settings{};
	};

}