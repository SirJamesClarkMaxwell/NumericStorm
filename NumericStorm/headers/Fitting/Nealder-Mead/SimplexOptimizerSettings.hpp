#pragma once

#include "Model.hpp"
#include "ErrorModel.hpp"
#include "OptimizerSettings.hpp"


namespace NumericStorm::Fitting
{
using namespace NumericStorm::Concepts;

	template <Model M>
	class SimplexOptimizerSettings
	{
	public:
	
		virtual ~SimplexOptimizerSettings() = default;
	
		const M& getFunctionModel() const { return m_functionModel; };
		const ErrorModel& getErrorModel() const { return m_errorModel; }
		double getMinError() const { return m_minError; }
		long int getMaxIteration() const { return m_maxIteration; }
		bool getUseBounds() const { return m_useBounds; }
		

		friend class SimplexOptimizerSettingsBuilderBase;


	private:
		M m_functionModel{};
		ErrorModel m_errorModel{};
	
		long int m_maxIteration{ 1000 };
		double m_minError{ 0.1 };
		bool m_useBounds{ false };
	
	protected:
	
		template<class BuildingType, OptimizerSettings Settings>
		class SimplexOptimizerSettingsBuilderBase {
	
		public:
	
			Settings build() { return m_settingsObject; }
			
	
			BuildingType& functionModel(const M& model)
			{
				this->m_settingsObject.m_functionModel = model;
				return returnSelf();
			}
	
			BuildingType& errorModel(const ErrorModel& model)
			{
				this->m_settingsObject.m_errorModel = model;
				return returnSelf();
			}
	
			BuildingType& maxIteration(long int iterations)
			{
				this->m_settingsObject.m_maxIteration = iterations;
				return returnSelf();
			}
			BuildingType& minError(double error)
			{
				this->m_settingsObject.m_minError = error;
				return returnSelf();
			}
			BuildingType& useBounds(bool useBounds)
			{
				this->m_settingsObject.m_useBounds = useBounds;
				return returnSelf();
			}
			
		protected:
			BuildingType& returnSelf() { return static_cast<BuildingType&>(*this); }
	
		protected:
			Settings m_settingsObject{};
	
		};
		
	};
}
