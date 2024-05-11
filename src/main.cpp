#include <iostream>
#include "NumericStorm.hpp"
#include "../headers/FittingSandBoxFunctions.hpp"
#include <execution>
using namespace NumericStorm::Fitting;
void myOwnFunction(Data2& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
{
	auto& [A, mu, sigma, c] = parameters.getParameters();
	auto x = datum.get(0);  // Get x-values
	auto f = datum.get(1);  // Get f-values

	for (int i = 0; i < x.size() - 1; i++)
	{
		double updatedX = (x[i] - mu);
		f[i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
	}
	datum.set(f, 1);
};
void myOwnFunction2(Data3& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
{
	auto& [A, mu, sigma, c] = parameters.getParameters();
	auto x = datum.get(0);  // Get x-values
	auto f = datum.get(1);  // Get f-values

	for (const auto& item : datum)
	{
		double updatedX = (*item[0] - mu);
		*item[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
	}
	datum.set(f, 1);
};
int main()
{
	int iteartionCount = 10000000; // 10 M
	int size = 501;
	double firstTime, secondTime, thirdTime;
	//testingParameters();

	{
		std::cout << "First Data implementation as vector of vectors";
		Timer timer;

		for (int i = 0; i < iteartionCount; i++)
			testingModelAndErrorModel();
		firstTime = timer.stop();
	}
	std::cout << std::endl << std::endl;
	{
		std::cout << "Second Data implementation pre allocated block of memory, without iterators and returning the memory addresses ";
		std::vector<double> arguments(size);

		for (int i = 0; i < size; i++)
			arguments[i] = i;
		AdditionalParameters additionalParameters;
		Parameters<4> parameters{ {3,1,2,-1} }; // a,mu,sigma,shift 
		Timer timer;
		for (int c = 0; c < iteartionCount; c++)
		{
			Data2 data2(2, 501);
			for (int i = 0; i < 2; i++)
				data2.set(arguments, i);
			std::vector<double> values = data2.get(1);
			myOwnFunction(data2, parameters, additionalParameters);
		}
		secondTime = timer.stop();
	}
	{
		std::cout << "Third Data implementation pre allocated block of memory, with iterators and returning the memory addresses ";
		std::cout << std::endl << std::endl;
		std::vector<double> arguments(size);
		for (int i = 0; i < size; i++)
			arguments[i] = i;

		Parameters<4> parameters{ {3,1,2,-1} }; // a,mu,sigma,shift 
		AdditionalParameters additionalParameters;
		Timer timer;
		for (int c = 0; c < iteartionCount; c++)
		{

			Data3 data3(2, 501);
			for (int i = 0; i < 2; i++)
				data3.set(arguments, i);

			myOwnFunction2(data3, parameters, additionalParameters);
		}
		thirdTime = timer.stop();
	}

	std::cout << "First implementation: time per iteration " << firstTime / iteartionCount << std::endl;
	std::cout << "Second implementation: time per iteration " << secondTime / iteartionCount << std::endl;
	std::cout << "Third implementation: time per iteration " << thirdTime / iteartionCount << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "firstTime / secondTime " << firstTime / secondTime << "% faster" << std::endl;
	std::cout << "secondTime / thirdTime " << secondTime / thirdTime << "% faster" << std::endl;
	std::cout << "firstTime / thirdTime " << firstTime / thirdTime << "% faster" << std::endl;
	//std::cin.get();




	return 0;
}