#include "FittingTestsSetUp.hpp"


using namespace NumericStorm::Fitting;

namespace TestingErrorModel
{


struct TestingErrorModel : public ::testing::Test
{
	UsefulObjects objs{};
};

TEST_F(TestingErrorModel, TestingErrorModelInChi2ErrorModel)
{
	double testedError = objs.eModel(objs.true_datum, objs.evaluated_datum);
	EXPECT_NEAR(testedError, objs.trueError, 0.01);
};
}