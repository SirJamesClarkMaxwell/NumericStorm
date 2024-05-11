#pragma once
#include "../headers/FittingSandBoxFunctions.hpp"

using namespace NumericStorm::Fitting;
void testingParameters() {

	std::cout << "-------------------------------" << std::endl;
	std::cout << "Testing Parameters " << std::endl;
	std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
	Parameters<4> parameters{ referencedArray };

	Parameters<3> parameters2({ 1.0, 2.0, 3.0 });
	std::cout << "Parameters: ";

	for (int i = 0; i < 3; i++)
		std::cout << i << ":" << parameters[i] << " ";
	std::cout << std::endl;

	for (int i = 0; i < 3; i++)
		std::cout << i << ":" << parameters2[i] << " ";
	std::cout << std::endl;

	// Access a parameter by index
	double& param_ref = parameters[0];
	param_ref = 4.0;
	std::cout << "Parameter 0: " << param_ref << std::endl;

}

void GaussianModel::gaussianFunction(Data& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
{
	auto& [A, mu, sigma, c] = parameters.getParameters();
	for (int i = 0; i < datum[0].size() - 1; i++)
	{
		double updatedX = (datum[0][i] - mu);
		datum[1][i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
	}
};
double Chi2ErrorModel::chi2ErrorModelFunction(const Data& referenceData, const Data& evaluatedData) {
	const std::vector<double>& referenceValues = referenceData[1];
	const std::vector<double>& evaluatedValues = evaluatedData[1];
	double chi2 = 0;
	for (size_t i = 0; i < referenceValues.size(); i++)
	{
		chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
	}
	return chi2;
}
void testingModelAndErrorModel()
{
	//std::cout << "-------------------------------" << std::endl;
	//std::cout << "Testing model and error model" << std::endl;
	std::vector<double> arguments;
	arguments.resize(500);
	for (int i = 0; i < 500; i++)
		arguments[i] = i;

	AdditionalParameters additionalParameters;

	Parameters<4> parameters{ {1,0,1,0} }; // A,mu,sigma,shift 
	Parameters<4> parameters2{ {3,1,2,-1} }; // a,mu,sigma,shift 

	Model model = GaussianModel();
	ErrorModel errorModel = Chi2ErrorModel();

	Data data1{ 2 }, data2{ 2 };
	data1[0] = arguments;
	data1[1] = arguments;
	data2[0] = arguments;
	data2[1] = arguments;

	model(data1, parameters, additionalParameters);
	model(data2, parameters2, additionalParameters);

	double error = errorModel(data1, data2);


	std::vector<double> calculatedValues1 = data1[1];
	std::vector<double> calculatedValues2 = data2[1];
	/*
		for (size_t i = 0; i < arguments.size(); i++)
			std::cout << std::fixed << std::setprecision(2) << arguments[i];
		std::cout << std::endl << "value 1: ";
		for (size_t i = 0; i < arguments.size(); i++)
			std::cout << std::fixed << std::setprecision(2) << calculatedValues1[i];
		std::cout << std::endl << "value 2: ";
		for (size_t i = 0; i < arguments.size(); i++)
			std::cout << std::fixed << std::setprecision(2) << calculatedValues2[i];
		std::cout << std::endl;

		std::cout << "Error: " << error << std::endl;
		std::cout << "x: ";
		*/
};

