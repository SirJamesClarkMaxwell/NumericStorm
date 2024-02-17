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
#include "./Fitting/FitterSettings.hpp"

#include "./Fitting/Exceptions/NoSetErrorModelExeption.hpp"
#include "./Fitting/Exceptions/NoSetModelExeption.hpp"


#include "./Fitting/Nealder-Mead/SimplexFitter.hpp"
#include "./Fitting/Nealder-Mead/SimplexFigure.hpp"
#include "./Fitting/Nealder-Mead/SimplexPoint.hpp"


#include "./Fitting/Nealder-Mead/BasicSimplex/BasicSimplexFitter.hpp"
#include "./Fitting/Nealder-Mead/BasicSimplex/BasicSimplexFitterSettings.hpp"

#include "./Fitting/Nealder-Mead/SimplexCreator/ISimplexFactory.hpp"
#include "./Fitting/Nealder-Mead/SimplexCreator/SimplexCreatorFactory.hpp"
#include "./Fitting/Nealder-Mead/SimplexCreator/SimplexCreatorSetting.hpp"

#include "./Fitting/Nealder-Mead/SimplexOperations/Reflection.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/Contraction.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/Expantion.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/Shrinking.hpp"

#include "./Fitting/Nealder-Mead/SimplexOperations/ReflectionOperationArguments.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/ContractionOperationArguments.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/ExpantionOperationArguments.hpp"
//#include "./Fitting/Nealder-Mead/SimplexOperations/ShrinkingOperationArguments.hpp"

#include "./Fitting/Nealder-Mead/SimplexOperations/ISimplexOperation.hpp"
#include "./Fitting/Nealder-Mead/SimplexOperations/SimplexOperationFactory.hpp"