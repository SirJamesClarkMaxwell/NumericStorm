#include <iostream>
#include "NumericStorm.hpp"
#include "../headers/FittingSandBoxFunctions.hpp"
using namespace NumericStorm::Fitting;

int main()
{
	//testingParameters();
	//testingModelAndErrorModel();
	Parameters<4> trueParameters({ 1,1,1,1 });
	Parameters<4> testingParameters({ 2,2,2,2 });

	AdditionalParameters additionalParameters{};

	Model model = GaussianModel();
	ErrorModel errorModel = Chi2ErrorModel();

	Data data1{ 2 };
	std::array<double, 100> arguments;
	int i = -50;
	for (int it = 0;it < 100;it++)
	{
		data1[0][it] = i++;
		data1[1][it] = i++;
	}
	Data data2 = Data(data1);
	model(data1, trueParameters, additionalParameters);


	using Builder = BasicSimplexFitterSettings<4, AdditionalParameters>::BasicSimplexSettingsBuilder;
	using Settings = BasicSimplexFitterSettings<4, AdditionalParameters>;
	using Fitter = BasicSimplexFitter<4, AdditionalParameters, Settings>;

	Builder builer = Builder(model, errorModel);
	builer.maxIteration(1000).minError(0.1).maxParameters(Parameters<4>({ 5,5,5,5 })).minParameters(Parameters<4>({ 0,0,0,0 }));


	Settings fitterSettings = builer.build();
	Fitter fitter(fitterSettings);
	fitter.setUp();
	fitter.fit(testingParameters, additionalParameters);

	return 0;
}