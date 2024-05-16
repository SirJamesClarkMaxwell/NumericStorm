#include "../headers/FittingSandBoxFunctions.hpp"

using namespace NumericStorm::Fitting;

void modelFunction(double& x, double& y, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters) {
	auto& [A, mu, sigma, c] = parameters.getParameters();

	double updatedX = (x - mu);
	y = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
}

void modelFunctionIteratedData(IteratedData& data, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters) {
	auto& [A, mu, sigma, c] = parameters.getParameters();

	for (auto col : data.columnOrder()) {
		double updatedX = (col[0] - mu);
		col[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;

		//std::cout << col[0] << " " << col[1] << std::endl;
	}

	
}

double errorFunctionData(const Data& d1, const Data& d2) {
	const std::vector<double>& referenceValues = d1[1];
	const std::vector<double>& evaluatedValues = d2[1];
	double chi2 = 0;
	for (size_t i = 0; i < referenceValues.size(); i++)
	{
		chi2 += pow((referenceValues[i] - evaluatedValues[i]), 2);
	}
	return chi2;
}

double errorFunctionIteratedData(IteratedData& d1, IteratedData& d2) {
	double chi2 = 0;
	auto iter1 = d1.columnOrder().begin();
	auto iter2 = d2.columnOrder().begin();
	auto end1 = d1.columnOrder().end();
	auto end2 = d2.columnOrder().end();

	for (; iter1 != end1 && iter2 != end2; iter1++, iter2++)
	{
		chi2 += pow((*iter1)[1] - (*iter2)[1], 2);
	}
	return chi2;
}

int iterationCount = 1000;
int pointCount = 32;

void testingIteratedDataClass() {
	std::vector<double> arguments;
	arguments.resize(pointCount);
	for (int i = 0; i < pointCount; i++)
		arguments[i] = i;

	AdditionalParameters additionalParameters;

	Parameters<4> parameters{ {1,0,1,0} }; // A,mu,sigma,shift 
	Parameters<4> parameters2{ {3,1,2,-1} }; // a,mu,sigma,shift 


	IteratedData data1{ 2, pointCount }, data2{ 2, pointCount };
	data1.set(arguments, 0);
	data1.set(arguments, 1);
	data2.set(arguments, 0);
	data2.set(arguments, 1);


	auto iter1 = data1.columnOrder().begin();
	auto iter2 = data2.columnOrder().begin();
	auto end1 = data1.columnOrder().end();
	auto end2 = data2.columnOrder().end();


	for (int i = 0; i < iterationCount; i++) {
		modelFunctionIteratedData(data1, parameters, additionalParameters);
		modelFunctionIteratedData(data2, parameters2, additionalParameters);

		double error = errorFunctionIteratedData(data1, data2);
	}
	
	//std::cout << std::endl << std::endl;
	//data1.presentData();
	//std::cout << std::endl << std::endl;
	//data2.presentData();
	//std::cout << std::endl << std::endl;

	

}

void testingDataClass()
{

	std::vector<double> arguments;
	arguments.resize(pointCount);
	for (int i = 0; i < pointCount; i++)
		arguments[i] = i;

	AdditionalParameters additionalParameters;

	Parameters<4> parameters{ {1,0,1,0} }; // A,mu,sigma,shift 
	Parameters<4> parameters2{ {3,1,2,-1} }; // a,mu,sigma,shift 


	Data data1{ 2 }, data2{ 2 };
	data1[0] = arguments;
	data1[1] = arguments;
	data2[0] = arguments;
	data2[1] = arguments;

	GaussianModel model{};

	for (int i = 0; i < iterationCount; i++) {
		model(data1, parameters, additionalParameters);
		model(data2, parameters2, additionalParameters);

		double error = errorFunctionData(data1, data2);
	}
	
	//int two = 1;
	//for (int i = 0; i < 2; i++) {
	//	for (auto item : data1[i]) {
	//		//std::cout << item << ((two++ % 2 == 0) ? "\n" : " ");
	//	}
	//}

	//std::cout << std::endl << std::endl;
	//two = 1;
	//for (int i = 0; i < 2; i++) {
	//	for (auto item : data2[i]) {
	//		//std::cout << item << ((two++ % 2 == 0) ? "\n" : " ");
	//	}
	//}

	
};

