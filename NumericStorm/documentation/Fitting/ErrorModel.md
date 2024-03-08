# ErrorModel class

The ErrorModel class is an abstract base class that defines the interface for all error models used in the fitting process.

An error model is a function that maps a pair of data points to a scalar error value. The error model is used to quantify the uncertainty associated with a fitted curve or surface.

The ErrorModel class provides a virtual operator() method that must be implemented by derived classes. The operator() method takes two data points (referencedData and comparedData) as input and returns a double value that represents the error between the two data points.

## Member functions

```cpp
ErrorModel(std::function<double(const Data& referenceData, const Data& evaluatedData)> errorModel)
```

The constructor that takes an error function.

```cpp
virtual double operator()(const Data& referencedData, const Data& comparedData) = 0;
```

Evaluates the error model.

## Example of usage

```cpp
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
		std::vector<double> getArguments() override {...};
		std::vector<double> getValues() override { ...};
	};

	std::unique_ptr<Data> gaussian(const std::vector<double> &arguments, const Parameters<4> &parameters, const AdditionalParameters &additionalParameters)
	    {...}

    double chi2ErrorModelFunction(const std::shared_ptr<Data> &referenceData, const std::shared_ptr<Data> &evaluatedData)
	{
		std::vector<double> referenceValues = referenceData->getValues();
		std::vector<double> evaluatedValues = evaluatedData->getValues();
		double chi2 = 0;

		for (size_t i = 0; i < referenceValues.size(); i++)
            chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
		return chi2;
    }



	int main()
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

        ErrorModel errorModel(chi2Model);
		double calculatedError = errorModel(referencedData, evaluatedData);
	};
```

or if you want you could write your own class for calculating the error and in your project use your own class, what we generally recommend.

```cpp
// includes
class Chi2ErrorModel : public ErrorModel
{
public:
	Chi2ErrorModel(std::function<double(const std::shared_ptr<Data> &, const std::shared_ptr<Data> &)> chi2Model)
        : ErrorModel(chi2Model) {}
	double operator()(const std::shared_ptr<Data> &referenceData, const std::shared_ptr<Data> &evaluatedData)
	{
		return this->m_errorModel(referenceData, evaluatedData);
	};
};

int main()
{
	Chi2ErrorModel errorModel(chi2Model);
	double calculatedError = errorModel(referencedData, evaluatedData);
	std::cout << "Calculated Error:" calculatedError <<std::endl;

}
```
