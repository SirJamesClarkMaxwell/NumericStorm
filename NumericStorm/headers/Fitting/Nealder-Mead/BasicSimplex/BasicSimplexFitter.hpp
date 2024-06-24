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
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings = BasicSimplexFitterSettings<parameter_size, AuxilaryParameters>>
class BasicSimplexFitter : public SimplexFitter<parameter_size, AuxilaryParameters, DerivedSettings>
{
public:

	BasicSimplexFitter() = delete; //todo set default configuration here
	BasicSimplexFitter(const DerivedSettings& settings, bool calculateUncertainty = false)
		:SimplexFitter<parameter_size, AuxilaryParameters, DerivedSettings>{ settings, calculateUncertainty } {};

	const int bestPoint = SimplexFigure<parameter_size>::bestPoint;

	virtual ~BasicSimplexFitter() = default;

	BasicSimplexFitter(SimplexFigure<parameter_size> simplexFigure)
		: SimplexFitter<parameter_size>{ simplexFigure } {}

	virtual void setUp() override
	{
		//* operations
		this->m_simplexOperationFactory.registerCreators<Reflection<parameter_size>,
			Expansion<parameter_size>,
			Contraction<parameter_size>,
			Shrinking<parameter_size>>(this->m_settings.m_simplexOperationSetUpInfo);

		//* creators
		this->m_simplexCreatorFactory.registerCreators<BasicSimplexCreator<parameter_size>>(this->m_settings.m_simplexCreatorSetUpInfo);

		//* strategy
		this->m_strategyManager.registerCreators<BasicSimplexDecision<parameter_size>>(this->m_settings.m_simplexStrategySetUpInfo);

	};


	virtual FittingResults<parameter_size> fit(const Parameters<parameter_size>& initialParameters, const AuxilaryParameters& additionalParameters) override {

		int iterationCount = 0;
		setUpFittingsProcedure(initialParameters, additionalParameters);
		SimplexIntermediatePoints<parameter_size> simplexIntermediatePoints{ this->m_simplexFigure,PIndices::PointCount };
		simplexIntermediatePoints.m_simplexFigure.sort();


		while (checkFittingConditions(iterationCount, simplexIntermediatePoints.m_simplexFigure[bestPoint]))
		{
			oneAlgorithmStep(simplexIntermediatePoints);
			auto params = simplexIntermediatePoints.m_simplexFigure[bestPoint].getParameters();
			double error = simplexIntermediatePoints.m_simplexFigure[bestPoint].getError();
			std::cout << "iteration: "<< iterationCount << " ";
			for (auto& item : params)
				std::cout << item << " ";
			std::cout << " error " << error << std::endl;
			std::cout << std::endl;
		}

		SimplexPoint<parameter_size> bestPointRes = simplexIntermediatePoints.m_simplexFigure[bestPoint];
		FittingResults<parameter_size> fittingResult{ bestPointRes.getParameters(), iterationCount, bestPointRes.getError() };
		return fittingResult;
	};


private:
	const bool checkFittingConditions(int& iter, const SimplexPoint<parameter_size>& bestPoint)
	{
		bool iterationCondition = iter++ >= this->m_settings.getMaxIteration();
		bool errorCondition = bestPoint.getError() >= this->m_settings.getMinError();
		return iterationCondition or errorCondition;
	}


	void setUpFittingsProcedure(const Parameters<parameter_size>& parameters, const AuxilaryParameters& additionalParameters)
	{
		SimplexPoint<parameter_size> initialPoint{ this->m_settings.getReferencedData(), parameters.getParameters() };

		//https://stackoverflow.com/questions/6610046/stdfunction-and-stdbind-what-are-they-and-when-should-they-be-used
		auto evalCallback = std::bind(&BasicSimplexFitter<parameter_size, AuxilaryParameters, DerivedSettings>::simplexPointEvaluationFunction, this,
			std::placeholders::_1,
			additionalParameters);

		initialPoint.onEvaluate(evalCallback);
		initialPoint.evaluatePoint();
#if DEBUG
		std::cout << "initial point: ";
		for (auto& item : initialPoint.getParameters())
			std::cout << item << " ";
		std::cout << " error " << initialPoint.getError() << std::endl;

#endif
		CreatorInput<parameter_size> creatorInput{ initialPoint, this->m_settings.parametersMinBounds, this->m_settings.parametersMaxBounds };
		this->m_simplexFigure = this->m_simplexCreatorFactory.invoke("basic", creatorInput);
		this->m_simplexFigure.sort();
	};


	void simplexPointEvaluationFunction(SimplexPoint<parameter_size>& point, const AuxilaryParameters& additionalParameters)
	{
		point.evaluatePoint(this->m_settings.m_functionModel, this->m_settings.m_errorModel, additionalParameters);
	}
#if DEBUG
public:
#endif
	void oneAlgorithmStep(SimplexIntermediatePoints<parameter_size>& intermediatePoints)
	{
		this->m_strategyManager.invoke("basic", intermediatePoints);
		this->m_simplexOperationFactory.invoke(intermediatePoints.m_currentOperation, intermediatePoints);
		intermediatePoints.m_simplexFigure.sort();
		intermediatePoints.m_simplexFigure.calculateCentroid();
	};

private:

	//FIXME  this is probably wrong, could you fix logic here, i am not sure that this is correct 
	//std::function<void(SimplexPoint<parameter_size>&)> evaluationFunction = std::bind(&BasicSimplexFitter::simplexPointEvaluationFunction, SimplexPoint<parameter_size>, AuxilaryParameters, std::placeholders::_2);


};




}