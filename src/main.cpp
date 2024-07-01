#include <iostream>
#include <concepts>
#include "NumericStorm.hpp"
#include "../headers/FittingSandBoxFunctions.hpp"
using namespace NumericStorm::Fitting;
using namespace NumericStorm::SimulatedAnnealing;
double sum(const std::array<double, 4>& obj)
{
	return std::accumulate(obj.begin(), obj.end(), 0.0);
};
class SimplexPointWrapper
{
public:
	SimplexPointWrapper(SimplexPoint<4> referencePoint)
		:m_referencePoint{ referencePoint } {};
	double getEnergy(const SimplexPoint<4>& object) { return sum(object.getParameters()) / 4; };
	std::array<double, 4> doSerialize(const SimplexPoint<4>& point) { return point.getParameters(); };
	std::unique_ptr<SimplexPoint<4>> createObject(std::vector<double> inputData)
	{
		SimplexPoint<4> toReturn{ m_referencePoint };
		for (int i = 0; i < 4;i++)
			toReturn[i] = inputData[i];

		return std::make_unique<SimplexPoint<4>>(toReturn);
	};
private:
	SimplexPoint<4> m_referencePoint;

};
int main()
{
#if 0
	bool b1, b2, b3, b4;
	b1 = true or false;
	b2 = true and false;

	std::cout << "true or false: " << b1 << std::endl;
	std::cout << "true and false: " << b2 << std::endl;

	//testingParameters();
	//testingModelAndErrorModel();
	static_assert(std::derived_from<OptimizerSettings<4, AdditionalParameters>, OptimizerSettings<4, AdditionalParameters>> == true);
	static_assert(std::derived_from<SimplexSettings<4, AdditionalParameters>, OptimizerSettings<4, AdditionalParameters>> == true);
	static_assert(std::derived_from<BasicSimplexOptimizerSettings<4, AdditionalParameters>, OptimizerSettings<4, AdditionalParameters>> == true);

	static_assert(std::derived_from<IDecision<4>, CreatorInterface<SimplexIntermediatePoints<4>&, bool, StrategySettings>> == true);
	static_assert(std::derived_from<ISimplexOperation<4>, CreatorInterface<SimplexIntermediatePoints<4>&, void, SimplexOperationSettings>> == true);
	static_assert(std::derived_from<IFigureCreator<4>, CreatorInterface<const CreatorInput<4>&, SimplexFigure<4>, SimplexCreatorSettings>> == true);

	static_assert(std::derived_from<BasicSimplexDecision<4>, CreatorInterface<SimplexIntermediatePoints<4>&, bool, StrategySettings>> == true);

	static_assert(std::derived_from<Reflection<4>, CreatorInterface<SimplexIntermediatePoints<4>&, void, SimplexOperationSettings>> == true);
	static_assert(std::derived_from<Expansion<4>, CreatorInterface<SimplexIntermediatePoints<4>&, void, SimplexOperationSettings>> == true);
	static_assert(std::derived_from<Contraction<4>, CreatorInterface<SimplexIntermediatePoints<4>&, void, SimplexOperationSettings>> == true);
	static_assert(std::derived_from<Shrinking<4>, CreatorInterface<SimplexIntermediatePoints<4>&, void, SimplexOperationSettings>> == true);

	static_assert(std::derived_from<BasicSimplexCreator<4>, CreatorInterface<const CreatorInput<4>&, SimplexFigure<4>, SimplexCreatorSettings>> == true);

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
		data1[0].push_back(i);
		data1[1].push_back(i);
		i++;
	}
	Data data2 = Data(data1);
	model(data1, trueParameters, additionalParameters);


	using BuilderAlias = BasicSimplexOptimizerSettings<4, AdditionalParameters>::BasicSimplexSettingsBuilder;
	using SettingsAlias = BasicSimplexOptimizerSettings<4, AdditionalParameters>;
	using FitterAlias = BasicSimplexOptimizer<4, AdditionalParameters, BasicSimplexOptimizerSettings<4, AdditionalParameters>>;

	BuilderAlias builder{ model, errorModel };
	CreatorSetUpInfo<SimplexCreatorSettings> sCreatorInfo{ "basic", SimplexCreatorSettings("basic", 0.0) };

	CreatorSetUpInfo<SimplexOperationSettings> sReflection{ "reflection", SimplexOperationSettings(1.2) };
	CreatorSetUpInfo<SimplexOperationSettings> sExpansion{ "expansion", SimplexOperationSettings(0.5) };
	CreatorSetUpInfo<SimplexOperationSettings> sContraction{ "contraction", SimplexOperationSettings(1.5) };
	CreatorSetUpInfo<SimplexOperationSettings> sShrinking{ "shrinking", SimplexOperationSettings(0.3) };

	CreatorSetUpInfo<StrategySettings> sStrategy{ "basic",  StrategySettings() };

	builder.maxIteration(1000)
		.minError(0.1)
		.maxParameters(Parameters<4>({ 5,5,5,5 }))
		.minParameters(Parameters<4>({ 0,0,0,0 }))
		.refData(std::make_shared<Data>(data2))
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
#endif


	{


		std::cout << "Testing SimulatedAnnealing" << std::endl;
		Parameters<4> trueParameters({ 1,1,1,1 });
		AdditionalParameters additionalParameters{};
		Model model = GaussianModel();
		ErrorModel errorModel = Chi2ErrorModel();
		Data data1{ 2 };
		std::array<double, 100> arguments;
		int i = -50;
		for (int it = 0;it < 100;it++)
		{
			data1[0].push_back(i);
			i++;
		}
		model(data1, trueParameters, additionalParameters);
		std::shared_ptr<Data> ptrData = std::make_shared<Data>(data1);
		SimplexPoint<4> point{ ptrData,{ 1,1,1,1 } };
		point.evaluatePoint(model, errorModel, additionalParameters);

		SimplexPointWrapper pointWrapper(point);
		SimulatedAnnealingFactoryTypeEnsure annealingFactory{ pointWrapper };

	}
	return 0;
}