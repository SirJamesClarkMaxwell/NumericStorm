#include <ranges>

#include "NumericStorm.hpp"
#include "../headers/FittingSandBoxFunctions.hpp"
using namespace NumericStorm::Fitting;
using namespace NumericStorm::Annealing;



int main()
{

	Parameters<3> trueParameters({ 1.7,3.5, 2.1});
	Parameters<3> initialParameters({ 3.0, 3.0, 3.0});


	Parameters<3> min({ -1.0, -1.0, -1.0});
	Parameters<3> max({ 2.0, 2.0, 2.0 });

	AdditionalParameters additionalParameters{};

	GaussianModel model{};
	Chi2ErrorModel errorModel{};

	Data trueData{ 2 };


	for (double it = -1.0;it <= 1.0; it += 0.05)
	{
		trueData[0].push_back(it);
		trueData[1].push_back(it);
	}

	model(trueData, trueParameters, additionalParameters);

	for (auto [a, b] : std::ranges::views::zip(trueData[0], trueData[1]))
	{
		std::cout << a << " " << b << std::endl;
	}


	using SSettings = BasicSimplexOptimizerSettings<GaussianModel>;
	typename SSettings::BasicSimplexSettingsBuilder builder{};

	builder.errorModel(errorModel)
		.addCreatorSettings({ min, max })
		.addOperationSettings({ { BasicOperationsEnum::Reflect, 1.2 },
								{ BasicOperationsEnum::Expand, 1.5 },
								{ BasicOperationsEnum::Contract, 0.6},
								{ BasicOperationsEnum::Shrink, 0.5 }
			})
		.minError(0.0000001)
		.maxIteration(3000);

	auto settings = builder.build();

	using ASettings = AnnealingOptimizerSettings<SSettings>;

	ASettings annealingOptimizerSettings{ settings };

	using AnnealingOptimizer = SimulatedAnnealingOptimizer<BasicSimplexOptimizer<SSettings, BasicAdapter>>;


	AnnealingSettingsBuilder annealingSettingsBuilder{};

	constexpr double BOLTZMANN_CONSTANT = 1.380649e-23;

	annealingSettingsBuilder.initialTemperature(200)
		.pointNumber(5)
		.coolingRate(5)
		.constantK(BOLTZMANN_CONSTANT)
		.noiseFactor(0.0);

	auto annealingSettings = annealingSettingsBuilder.build();

	annealingOptimizerSettings.setAnnealingSettings(annealingSettings);

	AnnealingOptimizer optimizer{ annealingOptimizerSettings };

	optimizer.setUp();

	Fitter<AnnealingOptimizer> fitter{ optimizer };

	auto result = fitter.fit(initialParameters, trueData, additionalParameters);

	auto& params = result.getWrappedState().getParameters();

	for (auto& param : params)
	{
		std::cout << param << std::endl;
	}

	std::cout << "Error: " << result.getWrappedState().getError() << std::endl;

	return 0;
}