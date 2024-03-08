#include "pch.h"

#include <functional>
#include <cmath>

using namespace NumericStorm::Fitting;

namespace TestingErrorModel
{

	class GaussianData : public Data
	{
	public:
		GaussianData(const std::vector<double> &arguments, const std::vector<double> &values)
			: Data(arguments, values) {}
		virtual ~GaussianData(){};
		std::vector<double> getArguments() override { return this->m_argumets; };
		std::vector<double> getValues() override { return this->m_values; };
	};

	std::unique_ptr<Data> gaussian(const std::vector<double> &arguments, const Parameters<4> &parameters, const AdditionalParameters &additionalParameters)
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
	double chi2ErrorModelFunction(const std::shared_ptr<Data> &referenceData, const std::shared_ptr<Data> &evaluatedData)
	{
		std::vector<double> referenceValues = referenceData->getValues();
		std::vector<double> evaluatedValues = evaluatedData->getValues();
		double chi2 = 0;

#if DEBUG
		std::vector<double> differences;
		differences.resize(referenceValues.size());
		std::vector<double> squaredDifferences;
		squaredDifferences.resize(referenceValues.size());
#endif

		for (size_t i = 0; i < referenceValues.size(); i++)
		{
#if DEBUG
			differences[i] = referenceValues[i] - evaluatedValues[i];
			squaredDifferences[i] = pow(differences[i], 2);
			chi2 += squaredDifferences[i]; // Calculate chi2 in debug mode as well
#else
			chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
#endif
		}

		return chi2;
	}

	struct TestingErrorModel : public testing::Test
	{
		std::array<double, 4> referencedArray{2, 1, 2, -1};
		std::array<double, 4> evaluatedArray{1, 1, 1, -1};

		Parameters<4> referencedParameters{referencedArray};
		Parameters<4> evaluatedParameters{evaluatedArray};

		std::vector<double> arguments{-2, -1, 0, 1, 2};
		AdditionalParameters additionalParameters{};
		std::shared_ptr<Data> referencedData = gaussian(arguments, referencedParameters, additionalParameters);
		std::shared_ptr<Data> evaluatedData = gaussian(arguments, evaluatedParameters, additionalParameters);

		std::function<double(const std::shared_ptr<Data> &referenceData, const std::shared_ptr<Data> &evaluatedData)> chi2Model = chi2ErrorModelFunction;
		double trueError = chi2ErrorModelFunction(referencedData, evaluatedData);
	};

	TEST_F(TestingErrorModel, TestingErrorModelInChi2ErrorModel)
	{
		ErrorModel errorModel(chi2Model);
		double testedError = errorModel(referencedData, evaluatedData);
		EXPECT_NEAR(testedError, trueError, 0.01);
	};

}