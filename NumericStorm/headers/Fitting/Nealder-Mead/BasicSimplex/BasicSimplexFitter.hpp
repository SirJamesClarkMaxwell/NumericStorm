#pragma once

#include "SimplexFitter.hpp"
#include "BasicSimplexFitterSettings.hpp"

#include "SimplexFigure.hpp"

#include "SimplexOperationsHeader.hpp"

#include "BasicSimplexCreator.hpp"
#include "SimplexCreatorFactory.hpp"

#include "StrategyManager.hpp"
#include "BasicSimplexStrategy.hpp"

//todo manage includes!
//todo make a nspch.h file
namespace NumericStorm::Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings = BasicSimplexFitterSettings<parameter_size>>
class BasicSimplexFitter : public SimplexFitter<parameter_size, AuxilaryParameters, DerivedSettings>
{
public:

	BasicSimplexFitter() = delete; //todo set default configuration here
	BasicSimplexFitter(const DerivedSettings& settings, bool calculateUncertainty = false)
		:SimplexFitter<parameter_size, AuxilaryParameters, DerivedSettings>{ settings, calculateUncertainty }
	{

	};

	virtual ~BasicSimplexFitter() = default;

	BasicSimplexFitter(SimplexFigure<parameter_size> simplexFigure)
		: SimplexFitter<parameter_size>{ simplexFigure } {}

	virtual void setUp() override
	{
		//* operations
		std::vector<CreatorSetUpInfo<SimplexOperationSettings>> operationSettings = this->m_settings->operationSetUpInfo;
		this->m_simplexOperationFactory.registerCreators<Reflection, Expansion, Contraction, Shrinking>(operationSettings);

		//* creators
		this->m_simplexCreatorFactory.registerCreators<BasicSimplexCreator<parameter_size>>(this->m_settings->creatorSettings);

		//* strategy
		this->m_strategyManager.registerStrategy<BasicSimplexDecision<parameter_size>>(this->m_settings->strategySettings);

	};
	virtual FittingResults<parameter_size> fit(const Parameters<parameter_size>& initialParameters, const AuxilaryParameters& additionalParameters) override {

		int iterationCount = 0;
		setUpFittingsProcedure(initialParameters);
		SimplexIntermediatePoints simplexIntermediatePoints{ this->m_simplexFigure,PIndices::PointCount };
		this->m_simplexFigure.sort();

		while (checkFittingConditions(iterationCount))
		{


		}

		SimplexPoint<parameter_size> bestPoint = simplexIntermediatePoints[bestPoint];
		FittingResults<parameter_size> fittingResult{ bestPoint.getParameters(), iterationCount, bestPoint.getError() };
		return fittingResult;
	};

private:
	const bool checkFittingConditions(int& iter, const SimplexPoint<parameter_size>& bestPoint)
	{
		bool iterationCondition = iter++ <= this->m_settings->getMaxIteration();
		bool errorCondition = bestPoint.getError() <= this->m_settings->getMinError();
		return iterationCondition && errorCondition;
	}
	void setUpFittingsProcedure(const Parameters& parameters)
	{
		SimplexPoint<parameter_size> initialPoint = SimplexPoint<parameter_size>{ this->m_settings.getReferenceData(), parameters.getParameters() };
		initialPoint.onEvaluate(simplexPointEvaluationFunction);
		initialPoint.evaluatePoint();
		CreatorInput<parameter_size> creatorInput{ {initialPoint, parametersMinBounds, parametersMaxBounds} };
		this->m_simplexFigure = this->m_simplexCreatorFactory.invoke("basic", creatorInput);
		this->m_simplexFigure.sort();

	};
	void simplexPointEvaluationFunction(SimplexPoint<parameter_size>& point, const AuxilaryParameters& additionalParameters)
	{
		point.evaluatePoint(this->m_settings->m_functionModel, this->m_settings->m_errorModel, additionalParameters);
	}
#if DEBUG
public:
#endif
	void oneAlgorithmStep(SimplexIntermediatePoints& intermediatePoints)
	{
		this->m_strategyManager.invoke("basic", intermediatePoints);
		this->m_simplexOperationFactory.invoke(intermediatePoints.m_currentOperation, intermediatePoints);
		this->intermediatePoints.m_simplexFigure.sort();
	};

private:

	//FIXME  this is probably wrong, could you fix logic here, i am not sure that this is correct 
	std::function<void(SimplexPoint<parameter_size>&)> evaluationFunction = std::bind(&BasicSimplexFitter::simplexPointEvaluationFunction, SimplexPoint<parameter_size>, AuxilaryParameters std::placeholders::_2);


};




}