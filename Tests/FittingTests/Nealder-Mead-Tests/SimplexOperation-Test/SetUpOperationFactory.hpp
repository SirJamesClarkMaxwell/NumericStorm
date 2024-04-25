#pragma once
#include "NumericStorm.hpp"
#include "../pch.h"
using namespace NumericStorm::Fitting;

struct OperationFactoryTest :public::testing::Test
{
    OperationFactoryTest()
    {
       
    };
   
    void SetUp();
    void registerAllOperations();
};
