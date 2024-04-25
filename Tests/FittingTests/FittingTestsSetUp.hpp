#pragma once
#include "../pch.h"
#include <functional>
#include <cmath>

using namespace NumericStorm::Fitting;

class Chi2ErrorModel : public ErrorModel {
public:

    Chi2ErrorModel() : ErrorModel{ chi2ErrorModelFunction } {}

    static double chi2ErrorModelFunction(const Data& referenceData, const Data& evaluatedData) {
        const std::vector<double>& referenceValues = referenceData[1];
        const std::vector<double>& evaluatedValues = evaluatedData[1];
        double chi2 = 0;
        for (size_t i = 0; i < referenceValues.size(); i++)
        {
#if DEBUG
            chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
#else
            chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
#endif
        }
        return chi2;
    }
};



class GaussianModel : public Model<4> {
public:
    GaussianModel() : Model<4>{ gaussianFunction } {};

    static void gaussianFunction(Data& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
    {
        double A = parameters[0];
        double mu = parameters[1];
        double sigma = parameters[2];
        double c = parameters[3];

        for (int i = 0; i < datum[0].size(); i++)
        {
            double updatedX = (datum[0][i] - mu);
            datum[1][i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
        }
    }
};


class UsefulObjects
{
public:
    UsefulObjects()
    {

        true_datum[0] = arguments;
        true_datum[1] = trueValues;

        evaluated_datum[0] = arguments;
        evaluated_datum[1] = arguments;

        gModel(evaluated_datum, evaluatedParameters, additionalParameters);

        trueError = Chi2ErrorModel::chi2ErrorModelFunction(true_datum, evaluated_datum);



    };

    std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
    std::array<double, 4> evaluatedArray{ 1, 1, 1, -1 };

    Parameters<4> referencedParameters{ referencedArray };
    Parameters<4> evaluatedParameters{ evaluatedArray };

    std::vector<double> arguments{ -2, -1, 0, 1, 2 };
    AdditionalParameters additionalParameters{};

    GaussianModel gModel{};
    Chi2ErrorModel eModel{};

    std::vector<double> trueValues{ -0.789201551,-0.264241118,0.557601566,1,0.557601566 };

    Data true_datum{ 2 }, evaluated_datum{ 2 };

    double evalError{};
    double trueError{};

    

};

