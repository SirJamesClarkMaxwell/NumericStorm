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
struct Times 
{
	Times() = default;
	Times(double firstImplementation, double firstImplementationDeep, double secondImplementation, double secondImplementationDeep)
		: firstImplementation(firstImplementation), firstImplementationDeep(firstImplementationDeep), secondImplementation(secondImplementation), secondImplementationDeep(secondImplementationDeep)
	{};
		double firstImplementation, firstImplementationDeep, secondImplementation, secondImplementationDeep;

};
Times tester()
{
	//std::cout << "First Data implementation as vector of vectors";
	double firstTime, secondTime;
	double dataClassTime, dataClassIteratorTime;
	{
		Timer timer;
		dataClassTime = testingDataClass();
		firstTime = timer.stop();
	}



	//std::cout << "Second Data implementation pre allocated block of memory, with iterators and returning the memory addresses ";
	//std::cout << std::endl << std::endl;

	{
		Timer timer;
		dataClassIteratorTime = testingIteratedDataClass();
		secondTime = timer.stop();
	}


	// std::cout << "First implementation: time per iteration " << firstTime / iterationCount << std::endl;
	// std::cout << "Second implementation: time per iteration " << secondTime / iterationCount << std::endl;
	// std::cout << std::endl << std::endl;
	// std::cout << "firstTime / secondTime " << firstTime / secondTime << " times faster" << std::endl;
	//std::cout << "firstTime / dataClassTime " << firstTime / secondTime << " times faster" << std::endl;
	//std::cout << "dataClassIteratorTime / dataClassTime " << dataClassIteratorTime / dataClassTime << " times faster" << std::endl;
	return Times(firstTime, dataClassTime, secondTime, dataClassIteratorTime);
}

/*
int main()
{
	int repeatCount = 10000;
	std::vector<Times>times(repeatCount);
	for (int i = 0; i <repeatCount; i++) {
		Times t = tester();
		times[i] = t;
	}
	double firstTime=0, dataClassTime=0, secondTime=0, dataClassIteratorTime=0;
	for (auto& item : times)
	{
		firstTime += item.firstImplementation;
		dataClassTime += item.firstImplementationDeep;
		secondTime += item.secondImplementation;
		dataClassIteratorTime += item.secondImplementationDeep;
	}
	firstTime /= repeatCount;
	dataClassTime /= repeatCount;
	secondTime /= repeatCount;
	dataClassIteratorTime /= repeatCount;

	std::cout << "firstTime / dataClassTime " << firstTime / secondTime << " times faster" << std::endl;
	std::cout << "dataClassIteratorTime / dataClassTime " << dataClassIteratorTime / dataClassTime << " times faster" << std::endl;
}
*/
int main() {
	int repeatCount = 1000;
	std::vector<Times> times(repeatCount);

	// Ensure the entire vector is filled
	for (int i = 0; i < repeatCount; i++) 
	{
		Timer repTimer;

		Times t = tester();
		times[i] = t;
		std::cout << "Iteration " << i << " takes " << repTimer.stop() << " ms" << std::endl;
	}

	// Initialize sums to 0
	double firstTime = 0, dataClassTime = 0, secondTime = 0, dataClassIteratorTime = 0;

	// Sum up the times
	for (const auto& item : times) {
		firstTime += item.firstImplementation;
		dataClassTime += item.firstImplementationDeep;
		secondTime += item.secondImplementation;
		dataClassIteratorTime += item.secondImplementationDeep;
	}

	// Calculate averages
	//firstTime /= repeatCount;
	//dataClassTime /= repeatCount;
	//secondTime /= repeatCount;
	//dataClassIteratorTime /= repeatCount;

	// Print results
	std::cout << "firstTime / secondTime: " << firstTime / secondTime << " times faster" << std::endl;
	std::cout << "dataClassTime/dataClassIteratorTime : " << dataClassTime/dataClassIteratorTime   << " times faster" << std::endl;

	return 0;
}