#pragma once

#include "../SimplexFigure.hpp"
#include "../SimplexFitter.hpp"
#include "../SimplexPoint.hpp"
#include "BasicSimplexFitterSettings.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"
#include "../SimplexCreator/SimplexCreatorFactory.hpp"
#include "../SimplexDecision/StrategyManager.hpp"
// TODO: write BasicSimplexFitter minimize implementation
namespace NumericStorm
{
	namespace Fitting
	{
		template <size_t parameter_size, class DerivedSettings = BasicSimplexFitterSettings<parameter_size>>
		class BasicSimplexFitter : public SimplexFitter<parameter_size, DerivedSettings>
		{
		public:
			BasicSimplexFitter() = delete;
			BasicSimplexFitter(const BasicSimplexFitter<parameter_size, DerivedSettings>&) = default;
			BasicSimplexFitter(BasicSimplexFitter<parameter_size, DerivedSettings>&&) = default;
			BasicSimplexFitter<parameter_size, DerivedSettings>& operator=(const BasicSimplexFitter<parameter_size, DerivedSettings>&) = default;
			BasicSimplexFitter<parameter_size, DerivedSettings>& operator=(BasicSimplexFitter<parameter_size, DerivedSettings>&&) = default;

			virtual ~BasicSimplexFitter() = default;

			BasicSimplexFitter(SimplexFigure<parameter_size> simplexFigure)
				: SimplexFitter<parameter_size>{ simplexFigure } {}

			virtual void setUp(const DerivedSettings& fitterSettings) override { 
				this->m_settings = std::make_unique<DerivedSettings>(fitterSettings); 
			
			}
			virtual void fit() override {
				int iter = 0;
				while (iter++ <= this->m_settings->getMaxIteration() && this->m_simplexFigure[parameter_size] <= this->m_settings->getMinError()) {
					this->m_simplexFigure.sort();
					
					do {

					} while (true);
				}

				
			}

		protected:
			SimplexOperationFactory<parameter_size> m_simplexOperationFactory{};
			SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory{};
			StrategyManager<parameter_size> m_strategyManager{};
		};

	}
}