#include <iostream>
#include <concepts>
#include "NumericStorm.hpp"
#include "../headers/FittingSandBoxFunctions.hpp"
#include <execution>
using namespace NumericStorm::Fitting;

//void myOwnFunction2(Data3& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
//{
//	auto& [A, mu, sigma, c] = parameters.getParameters();
//
//	/*for (auto item : datum.columnOrder())
//	{
//		double updatedX = (item[0] - mu);
//		item[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
//	}*/
//	std::for_each(datum.columnOrder().begin(), datum.columnOrder().end(), [&](Data3::Column col) {
//		double updatedX = (col[0] - mu);
//		col[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
//		});
//
//};

extern int iterationCount;
extern int pointCount;
struct Times 
{
	Times() = default;
	Times(double firstImplementation, double firstImplementationDeep, double secondImplementation, double secondImplementationDeep)
		: firstImplementation(firstImplementation), firstImplementationDeep(firstImplementationDeep), secondImplementation(secondImplementation), secondImplementationDeep(secondImplementationDeep)
	{};
		double firstImplementation, firstImplementationDeep, secondImplementation, secondImplementationDeep;

};
Times tester()
{
	//std::cout << "First Data implementation as vector of vectors";
	double firstTime, secondTime;
	double dataClassTime, dataClassIteratorTime;
	{
		Timer timer;
		dataClassTime = testingDataClass();
		firstTime = timer.stop();
	}



	//std::cout << "Second Data implementation pre allocated block of memory, with iterators and returning the memory addresses ";
	//std::cout << std::endl << std::endl;

	{
		Timer timer;
		dataClassIteratorTime = testingIteratedDataClass();
		secondTime = timer.stop();
	}


	// std::cout << "First implementation: time per iteration " << firstTime / iterationCount << std::endl;
	// std::cout << "Second implementation: time per iteration " << secondTime / iterationCount << std::endl;
	// std::cout << std::endl << std::endl;
	// std::cout << "firstTime / secondTime " << firstTime / secondTime << " times faster" << std::endl;
	//std::cout << "firstTime / dataClassTime " << firstTime / secondTime << " times faster" << std::endl;
	//std::cout << "dataClassIteratorTime / dataClassTime " << dataClassIteratorTime / dataClassTime << " times faster" << std::endl;
	return Times(firstTime, dataClassTime, secondTime, dataClassIteratorTime);
}

/*
int main()
{


	

	Parameters<4> trueParameters({ 1,1,1,1 });
	Parameters<4> testingParameters({ 2,2,2,2 });

	AdditionalParameters additionalParameters{};

	Model model = GaussianModel();
	ErrorModel errorModel = Chi2ErrorModel();

	Data data1{ 2 };
	std::array<double, 100> arguments;
	double i = -2.0;
	for (int it = 0;it < 100;it++)
	{
		data1[0].push_back(i += 0.04);
		data1[1].push_back(i);
	}

	model(data1, trueParameters, additionalParameters);


	using BuilderAlias = BasicSimplexFitterSettings<4, AdditionalParameters>::BasicSimplexSettingsBuilder;
	using SettingsAlias = BasicSimplexFitterSettings<4, AdditionalParameters>;
	using FitterAlias = BasicSimplexFitter<4, AdditionalParameters, BasicSimplexFitterSettings<4, AdditionalParameters>>;

	BuilderAlias builder{ model, errorModel };
	CreatorSetUpInfo<SimplexCreatorSettings> sCreatorInfo{ "basic", SimplexCreatorSettings("basic", 0.0) };

	CreatorSetUpInfo<SimplexOperationSettings> sReflection{ "reflection", SimplexOperationSettings(1.5) };
	CreatorSetUpInfo<SimplexOperationSettings> sExpansion{ "expansion", SimplexOperationSettings(0.3) };
	CreatorSetUpInfo<SimplexOperationSettings> sContraction{ "contraction", SimplexOperationSettings(1.5) };
	CreatorSetUpInfo<SimplexOperationSettings> sShrinking{ "shrinking", SimplexOperationSettings(0.3) };

	CreatorSetUpInfo<StrategySettings> sStrategy{ "basic",  StrategySettings() };

	builder.maxIteration(1000)
		.minError(0.1)
		.maxParameters(Parameters<4>({ 2,2,2,2 }))
		.minParameters(Parameters<4>({ 0,0,0,0 }))
		.refData(std::make_shared<Data>(data1))
		.addCreatorSettings(sCreatorInfo)
		.addOperationSettings(sReflection)
		.addOperationSettings(sExpansion)
		.addOperationSettings(sContraction)
		.addOperationSettings(sShrinking)
		.addStrategySettings(sStrategy);


	SettingsAlias fitterSettings = builder.build();
	FitterAlias fitter(fitterSettings);
	fitter.setUp();
	auto results = fitter.fit(testingParameters, additionalParameters);

	return 0;
}