#pragma once
#include "NumericStorm.hpp"
#include "pch.h"
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
class GaussianModel : public Model<4> {
public:
    // No need for constructor parameters
    GaussianModel() : Model<4>(gaussianFunction) {};

    static std::unique_ptr<Data> gaussianFunction(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
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
    std::shared_ptr<Data> operator()(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters) {
        return Model::operator()(arguments, parameters, additionalParameters); // Call the static function
    };
};

class Chi2ErrorModel : public ErrorModel {
public:
    // No need for constructor parameters
    Chi2ErrorModel() : ErrorModel(chi2ErrorModelFunction) {}

    static double chi2ErrorModelFunction(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData) {
        std::vector<double> referenceValues = referenceData->getValues();
        std::vector<double> evaluatedValues = evaluatedData->getValues();
        double chi2 = 0;
        for (size_t i = 0; i < referenceValues.size(); i++)
        {
#if DEBUG
            chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
            // std::cout << chi2 << std::endl;
#else
            chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
#endif
        }
        return chi2;
    }

    double operator()(const std::shared_ptr<Data>& referenceData, const std::shared_ptr<Data>& evaluatedData) {
        return chi2ErrorModelFunction(referenceData, evaluatedData); // Call the static function
    };
};

struct OperationFactoryTest :public::testing::Test
{
    OperationFactoryTest()
    {
        expansionMaker = std::make_shared<Expansion<4>>(Expansion<4>{expansionOperationSettings});
        reflectionMaker = std::make_shared<Reflection<4>>(Reflection<4>{simplexOperationSettings});
        contractionMaker = std::make_shared<Contraction<4>>(Contraction<4>{simplexOperationSettings});
        shrinkingMaker = std::make_shared<Shrinking<4>>(Shrinking<4>{simplexOperationSettings});
    };
    std::vector<double> arguments{ -2, -1, 0, 1, 2 };
    std::array<double, 5> numbersToSimplexFigure{ 1.1, 1.3, 2, 2.1, 2.2 };
    SimplexFigure<4> basicSimplexFigure;
    AdditionalParameters additionalParameters{};
    std::shared_ptr<Model<4>> gaussianModel;
    std::shared_ptr<ErrorModel> chi2ErrorModel;
    SimplexPoint<4> referencedPoint;

    std::shared_ptr<Data> referencedData;

    SimplexOperationFactory<4> testedSimplexOperationFactory{};
    SimplexOperationSettings simplexOperationSettings{ 0.5 };
    SimplexOperationSettings expansionOperationSettings{ 2 };
    std::shared_ptr<Reflection<4>> reflectionMaker;
    std::shared_ptr<Expansion<4>> expansionMaker;
    std::shared_ptr<Contraction<4>> contractionMaker;
    std::shared_ptr<Shrinking<4>> shrinkingMaker;

    void SetUp();
};
