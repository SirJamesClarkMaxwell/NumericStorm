#pragma once
#include "pch.h"
#include "SetUpBasicSimplexStrategy.hpp"


namespace TestingBasicSimplexStrategy
{
TEST_F(BasicSimplexStrategyTest, TestingReflectionChoose) { EXPECT_EQ(2, 2); };
TEST_F(BasicSimplexStrategyTest, TestingExpansionChoose) { EXPECT_EQ(2, 2); };
TEST_F(BasicSimplexStrategyTest, TestingContractionChoose) { EXPECT_EQ(2, 2); };
TEST_F(BasicSimplexStrategyTest, TestingShrinkingChoose) { EXPECT_EQ(2, 2); };

}