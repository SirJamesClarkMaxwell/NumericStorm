#pragma once

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <functional>


#include "./Fitting/Fitter.hpp"
#include "./Fitting/Parameters.hpp"
#include "./Fitting/Data.hpp"
#include "./Fitting/Model.hpp"
#include "./Fitting/AdditionalParameters.hpp"
#include "./Fitting/ErrorModel.hpp"
#include "./Fitting/FitterSettings.hpp"

#include "./Fitting/Exeptions/NoSetErrorModelExeption.hpp"
#include "./Fitting/Exeptions/NoSetModelExeption.hpp"


#include "./Fitting/Nealder-Mead/SimplexFitter.hpp"
#include "./Fitting/Nealder-Mead/SimplexFigure.hpp"
#include "./Fitting/Nealder-Mead/SimplexPoint.hpp"
