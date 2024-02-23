#include "pch.h"

using namespace NumericStorm::Fitting;

namespace TestingParameters {

class MockParameters : public Parameters<3> {
public:
    MockParameters(std::array<double, 3> parameters)
        : Parameters(parameters) {}

    double& operator [](int index) override {
        return m_parameters[index];
    }

    std::array<double, 3> getParameters() override {
        return m_parameters;
    }

    double getError() override {
        return m_error;
    }
};

TEST(ParametersTest, Initialization) {
    std::array<double, 3> params = {1.0, 2.0, 3.0};
    MockParameters mockParams(params);

    EXPECT_EQ(mockParams[0], 1.0);
    EXPECT_EQ(mockParams[1], 2.0);
    EXPECT_EQ(mockParams[2], 3.0);
    EXPECT_EQ(mockParams.getError(), -1);
}
    
}