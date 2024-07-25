#pragma once

#include <vector>

#include "Model.hpp"
#include "OptimizerSettings.hpp"
#include "SimplexOptimizerSettings.hpp"
#include "Parameters.hpp"
#include "SimplexIntermediateState.hpp"
#include "BasicOperationsEnum.hpp"
#include "BasicSimplexIndeciesEnum.hpp"

#include "SimplexCreatorSettings.hpp"
#include "SimplexStrategySettings.hpp"
#include "SimplexOperationSettings.hpp"
#include "SimplexOptimizationResults.hpp"


namespace NumericStorm::Fitting
{
	using namespace NumericStorm::Concepts;

	template<Model M>
	class BasicSimplexOptimizerSettings : public SimplexOptimizerSettings<M>
	{
	public:
		static const size_t parameter_size = M::parameter_size;
		using AuxilaryParameters = typename M::AuxilaryParameters;
		using OptimizerInputT = Parameters<parameter_size>;
		using OptimizerStateT = SimplexIntermediateState<parameter_size, BasicSimplexIndeciesEnum, BasicOperationsEnum>;
		using OptimizerOutputT = SimplexOptimizationResults<parameter_size>;
		
		virtual ~BasicSimplexOptimizerSettings() = default;
	
		const auto& getCreatorSettings() const
		{
			return m_creatorSettings;
		}

		const auto& getStrategySettings() const
		{
			return m_strategySettings;
		}

		const auto& getOperationSettings() const
		{
			return m_operationSettings;
		}

	protected:
		SimplexCreatorSettings<parameter_size> m_creatorSettings{};
		SimplexStrategySettings<parameter_size> m_strategySettings{};

		using SettingsPair = std::pair<BasicOperationsEnum, SimplexOperationSettings<parameter_size>>;
		std::vector<SettingsPair> m_operationSettings{BasicOperationsEnum::OpCount};

		friend class BasicSimplexOptimizerSettingsBuilderBase;
		friend class BasicSimplexSettingsBuilder;
	
	protected:
		
	
		template<class BuildingType, OptimizerSettings Settings>
		class BasicSimplexOptimizerSettingsBuilderBase : public SimplexOptimizerSettings<M>::SimplexOptimizerSettingsBuilderBase<BuildingType, Settings> {
		public:

			BuildingType& addOperationSettings(const SettingsPair& settings)
			{
				this->m_settingsObject.m_operationSettings[settings.first()] = settings.second();
				return this->returnSelf();
			}
			BuildingType& addOperationSettings(const std::vector<SettingsPair>& settings)
			{
				this->m_settingsObject.m_operationSettings = settings;
				return this->returnSelf();
			}
			BuildingType& addCreatorSettings(const SimplexCreatorSettings<parameter_size>& settings)
			{
				this->m_settingsObject.m_creatorSettings = settings;
				return this->returnSelf();
			}
			BuildingType& addStrategySettings(const SimplexStrategySettings<parameter_size>& settings)
			{
				this->m_settingsObject.m_strategySettings = settings;
				return this->returnSelf();
			}
		};
	
	public:
	
		class BasicSimplexSettingsBuilder : public BasicSimplexOptimizerSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexOptimizerSettings<M>> {};
	
		
	
	
	};

}






