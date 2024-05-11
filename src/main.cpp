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
	// auto x = datum.get(0);  // Get x-values
	 auto f = datum.get(1);  // Get f-values

	//for (Data3Iterator item = datum.begin();item!=datum.end();item++)
	 for (Data3Iterator item = datum.begin();item!=datum.end();item++)
	{
		*item[1] = 2 * (*item[0]);
		//bool b = item.m_ptr == datum.end().m_ptr;
		//std::cout << item.m_ptr <<" " << datum.end().m_ptr <<" " << b << std::endl;

		std::cout << "x: "<< *item[0] << " y: " << *item[1] << std::endl;
		//std::cout
		 /*double updatedX = (*item[0] - mu);
		 *item[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;*/
	}
	 datum.set(f, 1);
};
int main()
{
	int iteartionCount = 1000; // 1000 M
	int size = 501;
	double firstTime, secondTime, thirdTime;
	//testingParameters();
#if 0
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
#endif
	{
		std::cout << "Third Data implementation pre allocated block of memory, with iterators and returning the memory addresses ";
		std::cout << std::endl << std::endl;
		std::vector<double> arguments(size);
		for (int i = 0; i < size; i++)
			arguments[i] = i;

		Parameters<4> parameters{ {3,1,2,-1} }; // a,mu,sigma,shift 
		AdditionalParameters additionalParameters;
		Timer timer;
		//for (int c = 0; c < iteartionCount; c++)
		//{

			Data3 data3(2, 10);
			for (int i = 0; i < 2; i++)
				data3.set(arguments, i);
			myOwnFunction2(data3, parameters, additionalParameters);
			data3.presentData();
		//for (Data3Iterator it = data3.begin(); it != data3.end();it++) 
		//{
		//	*it[1] = 2 * (*it[0]);
		//	//std::cout << "x: " << *it[0] << " y: " << *it[1] << std::endl;
		//}
		//data3.presentData();
		//}
		//thirdTime = timer.stop();
	}

	#if 0 
	std::cout << "First implementation: time per iteration " << firstTime / iteartionCount << std::endl;
	std::cout << "Second implementation: time per iteration " << secondTime / iteartionCount << std::endl;
	std::cout << "Third implementation: time per iteration " << thirdTime / iteartionCount << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "firstTime / secondTime " << firstTime / secondTime << "% faster" << std::endl;
	std::cout << "secondTime / thirdTime " << secondTime / thirdTime << "% faster" << std::endl;
	std::cout << "firstTime / thirdTime " << firstTime / thirdTime << "% faster" << std::endl;
#endif
	//std::cin.get();
	return 0;
}