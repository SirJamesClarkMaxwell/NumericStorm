#include "pch.h"
#include <functional>
#include <cmath>

using namespace NumericStorm::Fitting;

namespace TestingModel 
{
	
class GaussianData :public Data
{
public:
	GaussianData(const std::vector<double>& arguments, const std::vector<double>& values)
		:Data(arguments,values){}
	virtual ~GaussianData() {};
	std::vector<double> getArguments() override { return this->m_argumets; };
	std::vector<double> getValues() override { return this->m_values; };


};

class GaussianModel :public Model<4>
{
public:
	GaussianModel(std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<4>& parameters,
		const AdditionalParameters& additionalParameters)> model) 
	:Model(model){};
	virtual ~GaussianModel() {};
	virtual std::unique_ptr<Data> operator()(const std::vector<double>& arguments, const Parameters<4>& parameters,
		const AdditionalParameters& additionalParameters) override
	{
		return m_model(arguments,parameters,additionalParameters);
	}

};
std::unique_ptr<Data> gaussian(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
{
	std::vector<double> calculateData;
	calculateData.resize(arguments.size());
	double A = parameters[0];
	double mu = parameters[1];
	double sigma = parameters[2];
	double c = parameters[3];



	for (int i = 0; i < arguments.size(); i++)
	{
		double updatedX = (arguments[i] - mu);
		calculateData[i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
	}

	return std::make_unique<GaussianData>(arguments, calculateData);
}
//using GaussianFunction = 
struct TestingGaussianModel:public testing::Test
{
	std::array<double, 4> parametersArray{ 2,1,2,-1 };
	Parameters<4> initialParameters{ parametersArray };
	
	std::vector<double> arguments{ -2,-1,0,1,2	};
	AdditionalParameters additionalParameters{};
	std::unique_ptr<Data> realData = gaussian(arguments, initialParameters, additionalParameters);
	//std::vector<double> trueValues{ -0.789201551,-0.264241118,0.557601566,1,0.557601566 };
	std::vector<double> trueValues = (*realData).getValues();

	std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)> gaussianFunction = gaussian;


};

TEST_F(TestingGaussianModel, TestingSimpleGaussianModel) 
{
	Model<4>* testedModel = new GaussianModel(gaussian);

	std::unique_ptr<Data> testedData = (*testedModel)(arguments, initialParameters, additionalParameters);
	auto testedValues = (*testedData).getValues();
	for (int i = 0; i < arguments.size(); i++)
		EXPECT_DOUBLE_EQ(testedValues[i],trueValues[i]);
};
}