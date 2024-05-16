#include <iostream>
#include "NumericStorm.hpp"
#include "../headers/FittingSandBoxFunctions.hpp"
#include <execution>
using namespace NumericStorm::Fitting;

//void myOwnFunction2(Data3& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
//{
//	auto& [A, mu, sigma, c] = parameters.getParameters();
//
//	/*for (auto item : datum.columnOrder())
//	{
//		double updatedX = (item[0] - mu);
//		item[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
//	}*/
//	std::for_each(datum.columnOrder().begin(), datum.columnOrder().end(), [&](Data3::Column col) {
//		double updatedX = (col[0] - mu);
//		col[1] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
//		});
//
//};

extern int iterationCount;
extern int pointCount;

void tester() {
	std::cout << "First Data implementation as vector of vectors";
	double firstTime, secondTime;
	{
		Timer timer;
		testingDataClass();
		firstTime = timer.stop();
	}



	std::cout << "Second Data implementation pre allocated block of memory, with iterators and returning the memory addresses ";
	std::cout << std::endl << std::endl;

	{
		Timer timer;
		testingIteratedDataClass();
		secondTime = timer.stop();
	}


	std::cout << "First implementation: time per iteration " << firstTime / iterationCount << std::endl;
	std::cout << "Second implementation: time per iteration " << secondTime / iterationCount << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "firstTime / secondTime " << firstTime / secondTime << " times faster" << std::endl;
}

int main()
{
	for (int i = 0; i < 10; i++) {
		tester();
	}
	

	return 0;
}