#pragma once

#include <type_traits>
#include <concepts>
#include "OperationSettings.hpp"

namespace NumericStorm::Concepts {
	template <typename T>
	concept OperationBase = requires(T t, typename T::SettingsT settings) {
		typename T::SettingsT;
		requires OperationSettings<typename T::SettingsT>;
	
		{ t.updateSettings(settings) } -> std::same_as<void>;
		{ t.getSettings() } -> std::same_as<const typename T::SettingsT&>;
	};
}

