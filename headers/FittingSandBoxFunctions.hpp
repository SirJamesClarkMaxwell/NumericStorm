#pragma once 
#include <cmath>
#include <iomanip>
#include <tuple>
#include "NumericStorm.hpp"

using namespace NumericStorm::Fitting;
void testingParameters();

class GaussianModel : public Model<4>
{
public:
    GaussianModel()
        : Model<4>{ gaussianFunction } {}
    static void gaussianFunction(Data& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters);

};
class Chi2ErrorModel : public ErrorModel {
public:

    Chi2ErrorModel() : ErrorModel{ chi2ErrorModelFunction } {}

    static double chi2ErrorModelFunction(const Data& referenceData, const Data& evaluatedData);
};

void testingModelAndErrorModel();
