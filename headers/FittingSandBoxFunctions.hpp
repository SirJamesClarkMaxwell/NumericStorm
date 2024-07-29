#pragma once 

#include "NumericStorm.hpp"

using namespace NumericStorm::Fitting;


class GaussianModel : public ModelBase<3>
{
public:
    GaussianModel()
        : ModelBase<3>{ gaussianFunction } {}

    static void gaussianFunction(Data& datum, const Parameters<3>& parameters, const AdditionalParameters& additionalParameters);

};


class Chi2ErrorModel : public ErrorModel {
public:

    Chi2ErrorModel() : ErrorModel{ chi2ErrorModelFunction } {}

    static double chi2ErrorModelFunction(const Data& referenceData, const Data& evaluatedData);
};


class BasicAdapter {
public:
    using Input = AnnealingOptimizerState<SimplexIntermediateState<3, BasicSimplexIndeciesEnum, BasicOperationsEnum>>;

    static void setUp(Input& input);
    static void update(Input& input);
};
