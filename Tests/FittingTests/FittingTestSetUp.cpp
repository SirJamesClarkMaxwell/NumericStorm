#include "FittingTestsSetUp.hpp"

std::unique_ptr<Data> gaussian(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters) {
    std::vector<double> calculateData;
    calculateData.resize(arguments.size());
    double A = parameters[0], mu = parameters[1], sigma = parameters[2], c = parameters[3];

    for (int i = 0; i < arguments.size(); i++)
    {
        double updatedX = (arguments[i] - mu);
        calculateData[i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
    }
    return std::make_unique<GaussianData>(arguments, calculateData);
};

double chi2ErrorModelFunction(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData)
{
    std::vector<double> referenceValues = referenceData->getValues();
    std::vector<double> evaluatedValues = evaluatedData->getValues();
    double chi2 = 0;
    for (size_t i = 0; i < referenceValues.size(); i++)
        chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
    return chi2;
}
