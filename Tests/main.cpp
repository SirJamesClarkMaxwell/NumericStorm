#include "pch.h"


using namespace NumericStorm::Fitting;
TEST(SomeTest, NameForSomeTest) 
{
	EXPECT_DOUBLE_EQ(3.3, NumericStorm::add(1.1, 2.2),0.001);
	std::cout << "some text" << std::endl;
}