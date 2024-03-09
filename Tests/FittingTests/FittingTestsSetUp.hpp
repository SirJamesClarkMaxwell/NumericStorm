#include "NumericStorm.hpp"
#include <iostream>

using namespace NumericStorm::Fitting;
class GaussianData : public Data
{
public:
    GaussianData(const std::vector<double>& arguments, const std::vector<double>& values)
        : Data(arguments, values) {}
    virtual ~GaussianData() {};
    std::vector<double> getArguments() override { return this->m_argumets; };
    std::vector<double> getValues() override { return this->m_values; };
};

std::unique_ptr<Data> gaussian(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
{
    std::vector<double> calculateData;
    calculateData.resize(arguments.size());
    double A = parameters[0], mu = parameters[1], sigma = parameters[2], c = parameters[3];

    for (int i = 0; i < arguments.size(); i++)
    {
        double updatedX = (arguments[i] - mu);
        calculateData[i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
    }
    return std::make_unique<GaussianData>(arguments, calculateData);
}
double chi2ErrorModelFunction(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData)
{
    std::vector<double> referenceValues = referenceData->getValues();
    std::vector<double> evaluatedValues = evaluatedData->getValues();
    double chi2 = 0;
    for (size_t i = 0; i < referenceValues.size(); i++)
        chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
    return chi2;
}
class Chi2ErrorModel : public ErrorModel
{
    //TODO: make function the actual function static and remove parameter form constructor
public:
    Chi2ErrorModel(std::function<double(const std::shared_ptr<Data>&, const std::shared_ptr<Data>&)> chi2Model)
        : ErrorModel(chi2Model) {}
    double operator()(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData)
    {
        return this->m_errorModel(referenceData, evaluatedData);
    };
};

class GaussianModel : public Model<4>
{
    //TODO: make function the actual function static and remove parameter form constructor
public:
    GaussianModel(std::function<std::unique_ptr<Data>(const std::vector<double>&, const Parameters<4>&, const AdditionalParameters&)> gaussian)
        :Model<4>(gaussian) {};
    std::unique_ptr<Data> operator()(const std::vector<double>& arguments, const Parameters<4>& parameters,
        const AdditionalParameters& additionalParameters) {
        return this->m_model(arguments, parameters, additionalParameters);
    };
};
class UsefullyObjects
{
public:
    UsefullyObjects()
    {
        std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
        std::array<double, 4> evaluatedArray{ 1, 1, 1, -1 };
        Parameters<4> referencedParameters{ referencedArray };
        Parameters<4> evaluatedParameters{ evaluatedArray };
        std::vector<double> arguments{ -2, -1, 0, 1, 2 };
        std::function<double(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData)> chi2Model = chi2ErrorModelFunction;
        std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)> gaussianFunction = gaussian;


        referencedData = gaussian(arguments, referencedParameters, additionalParameters);
        evaluatedData = gaussian(arguments, evaluatedParameters, additionalParameters);
        sharedPtrModel = std::make_shared<Model<4>>(Model<4>(gaussian));
        sharedPtrErrorModel = std::make_shared<ErrorModel>(ErrorModel(chi2ErrorModelFunction));

        trueError = chi2ErrorModelFunction(referencedData, evaluatedData);

        gaussianModel = std::make_shared<GaussianModel>(gaussianFunction);
        chi2ErrorModel = std::make_shared<Chi2ErrorModel>(chi2Model);
    };
    std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
    std::array<double, 4> evaluatedArray{ 1, 1, 1, -1 };

    Parameters<4> referencedParameters{ referencedArray };
    Parameters<4> evaluatedParameters{ evaluatedArray };

    std::vector<double> arguments{ -2, -1, 0, 1, 2 };
    AdditionalParameters additionalParameters{};
    std::shared_ptr<Data> referencedData;
    std::shared_ptr<Data> evaluatedData;

    double trueError;
    std::shared_ptr<Model<4>> sharedPtrModel;
    std::shared_ptr<ErrorModel> sharedPtrErrorModel;

    std::shared_ptr<Model<4>>  gaussianModel;
    std::shared_ptr<ErrorModel>  chi2ErrorModel;
};
