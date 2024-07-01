#pragma once

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <functional>
#include <algorithm>

#include "./Fitting/Fitter.hpp"
#include "./Fitting/Parameters.hpp"
#include "./Fitting/Data.hpp"
#include "./Fitting/Model.hpp"
#include "./Fitting/AdditionalParameters.hpp"
#include "./Fitting/ErrorModel.hpp"
#include "./Fitting/OptimizerSettings.hpp"
#include "./Fitting/Nealder-Mead/SimplexIntermediatePoints.hpp"

#include "./SimulatedAnnealig/SimulatedAnnealingFactory.hpp"
#include "./SimulatedAnnealig/TypeEnsureSimulatedAnnealing.hpp"

#include "./Fitting/Exceptions/NoSetErrorModelExeption.hpp"
#include "./Fitting/Exceptions/NoSetModelExeption.hpp"
#include "./Fitting/Exceptions/NoAvailableFactoryException.hpp"
#include "./Fitting/Exceptions/WrongTemplateArgument.hpp"

#include "./Fitting/Nealder-Mead/SimplexOptimizer.hpp"
#include "./Fitting/Nealder-Mead/SimplexFigure.hpp"
#include "./Fitting/Nealder-Mead/SimplexPoint.hpp"
#include "./Fitting/Nealder-Mead/SimplexSettings.hpp"
#include "./Fitting/Nealder-Mead/PIndices.hpp"


#include "./Fitting/Nealder-Mead/BasicSimplex/BasicSimplexOptimizer.hpp"
#include "./Fitting/Nealder-Mead/BasicSimplex/BasicSimplexOptimizerSettings.hpp"

#include "./Fitting/Nealder-Mead/SimplexCreator/IFigureCreator.hpp"
#include "./Fitting/Nealder-Mead/SimplexCreator/SimplexCreatorFactory.hpp"
#include "./Fitting/Nealder-Mead/SimplexCreator/SimplexCreatorSettings.hpp"

#include "./Fitting/Nealder-Mead/SimplexOperations/Reflection.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/Contraction.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/Expansion.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/Shrinking.hpp"

#include "./Fitting/Nealder-Mead/SimplexOperations/ISimplexOperation.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/SimplexOperationFactory.hpp"

#include "./Fitting/Nealder-Mead//SimplexDecision/BasicSimplexStrategy.hpp"
#include "./Fitting/Nealder-Mead//SimplexDecision/IDecision.hpp"
#include "./Fitting/Nealder-Mead//SimplexDecision/StrategyManager.hpp"


#include "./Fitting/Nealder-Mead/SimulatedAnnealingSimplexOptimizer/SimulatedAnnealingSimplexOptimizer.hpp"

