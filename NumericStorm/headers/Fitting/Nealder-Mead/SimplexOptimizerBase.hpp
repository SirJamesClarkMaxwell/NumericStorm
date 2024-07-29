#pragma once

#include "OptimizerSettings.hpp"
#include "SimplexOptimizerSettings.hpp"
#include "Model.hpp"
#include "OptimizerSettings.hpp"

namespace NumericStorm::Fitting
{
	using namespace NumericStorm::Concepts;

	template<class DerivedSettings>
	class SimplexOptimizerBase
	{
	public:
		SimplexOptimizerBase(const DerivedSettings& settings)
			: m_settings{ settings } {}

		auto getSettings() const
		{
			return m_settings;
		}

	protected:
		DerivedSettings m_settings;
	};


	template<Model M>
	using SimplexOptimizerBaseM = SimplexOptimizerBase<SimplexOptimizerSettings<M>>;

};
