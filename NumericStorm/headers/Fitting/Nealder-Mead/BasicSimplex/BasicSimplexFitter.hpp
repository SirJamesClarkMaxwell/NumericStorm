#pragma once

#include "../SimplexFigure.hpp"
#include "../SimplexFitter.hpp"
#include "../SimplexPoint.hpp"
#include "BasicSimplexFitterSettings.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"
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

			void setUp(const DerivedSettings& fitterSettings) override { this->m_settings = std::make_unique<DerivedSettings>(fitterSettings); }
			void fit() override {


				
			}

		private:
			SimplexOperationFactory<parameter_size> m_simplexOperationFactory;
		};

	}
}