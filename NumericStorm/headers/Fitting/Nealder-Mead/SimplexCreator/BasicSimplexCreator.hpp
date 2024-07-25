#pragma once

#include <array>

#include "VisitorOperationBase.hpp"
#include "SimplexCreatorSettings.hpp"
#include "Random.hpp"


namespace NumericStorm::Fitting {
	using namespace NumericStorm::Utils;

	template <size_t parameter_size>
	class BasicSimplexCreator : public VisitorOperationBase<SimplexCreatorSettings<parameter_size>>
	{
	public:
		using SettingsT = VisitorOperationBase<SimplexCreatorSettings<parameter_size>>::SettingsT;
		explicit BasicSimplexCreator(const SettingsT& settings)
			: VisitorOperationBase<SettingsT>{ settings } {}
	
	
		virtual ~BasicSimplexCreator() = default;
	
		typename SettingsT::Out operator()(const typename SettingsT::In& input) override {
			std::array<typename SettingsT::In, parameter_size + 1> points{};
			points.fill(input);
	
	
			std::for_each(points.begin() + 1, points.end(), [&](typename SettingsT::In& point) {

				std::transform(point.begin(), point.end(), point.begin(),
					[&](double value, size_t index) {
						return value + Random::Float(this->m_settings.getMinBounds()[index], this->m_settings.getMaxBounds()[index]);
					});
				point.evaluatePoint();
				});
	
	
			typename SettingsT::Out figure{ points };
			return figure;
		}
	};
}