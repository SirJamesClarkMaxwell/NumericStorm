#pragma once
#include "pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;


namespace TestingSimplexPointCopyConstructor
{
//* testing copy constructor
struct TestingCopyConstructor :public ::testing::Test, public UsefullyObjects
{
    TestingCopyConstructor()
        :baseSimplexPoint(arguments, referencedArray, additionalParameters) {

        baseSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);
        baseSimplexPoint.calculateError(referencedData);
        testingPoint = SimplexPoint<4>(baseSimplexPoint);
        };
    SimplexPoint<4> baseSimplexPoint;
    SimplexPoint<4> testingPoint;
};

// TEST_F(TestingCopyConstructor, arguments)
// {

//     std::vector<double> expectedArguments = baseSimplexPoint.getArguments();
//     std::vector<double> actualArguments = testingPoint.getArguments();
//     EXPECT_EQ(expectedArguments, actualArguments);
// }
TEST_F(TestingCopyConstructor, TestCopyConstructorArguments) {
    EXPECT_EQ(baseSimplexPoint.getArguments(), testingPoint.getArguments()) << "Arguments were not copied correctly using getArguments().";
}
TEST_F(TestingCopyConstructor, TestCopyConstructorModelSet) {
    EXPECT_EQ(baseSimplexPoint.modelIsSet(), testingPoint.modelIsSet()) << "ModelSet flag was not copied correctly using modelIsSet().";
}
TEST_F(TestingCopyConstructor, TestCopyConstructorErrorModelSet) {
    EXPECT_EQ(baseSimplexPoint.errorModelIsSet(), testingPoint.errorModelIsSet()) << "ErrorModelSet flag was not copied correctly using errorModelIsSet().";
}
TEST_F(TestingCopyConstructor, TestCopyConstructorModel) {
    // Note: Direct comparison of shared_ptrs. If you need to compare the underlying objects, you might need a custom method or logic.
    EXPECT_EQ(baseSimplexPoint.getModel(), testingPoint.getModel()) << "Model shared_ptr was not copied correctly using getModel().";
}
TEST_F(TestingCopyConstructor, TestCopyConstructorErrorModel) {
    // Note: Direct comparison of shared_ptrs. If comparing the underlying objects is needed, consider adding a method for that purpose.
    EXPECT_EQ(baseSimplexPoint.getErrorModel(), testingPoint.getErrorModel()) << "ErrorModel shared_ptr was not copied correctly using getErrorModel().";
}
TEST_F(TestingCopyConstructor, TestCopyConstructorError) {
    EXPECT_DOUBLE_EQ(baseSimplexPoint.getError(), testingPoint.getError()) << "Error value was not copied correctly using getError().";
}
//* testing assignment operator
}

namespace TestingSimplexPointAsigmentOperator
{
//* testing copy constructor
struct TestingAssignmentOperator :public ::testing::Test, public UsefullyObjects
{
    TestingAssignmentOperator()
        :baseSimplexPoint(arguments, referencedArray, additionalParameters) {

        baseSimplexPoint.setUp(sharedPtrModel, sharedPtrErrorModel);
        baseSimplexPoint.calculateError(referencedData);
        testingPoint = baseSimplexPoint;
    };
    SimplexPoint<4> baseSimplexPoint;
    SimplexPoint<4> testingPoint;
};

// TEST_FAsigmentOperatorCopyConstructor, arguments)
// {

//     std::vector<double> expectedArguments = baseSimplexPoint.getArguments();
//     std::vector<double> actualArguments = testingPoint.getArguments();
//     EXPECT_EQ(expectedArguments, actualArguments);
// }
TEST_F(TestingAssignmentOperator, TestAssigmentOperatorArguments) {
    EXPECT_EQ(baseSimplexPoint.getArguments(), testingPoint.getArguments()) << "Arguments were not copied correctly using getArguments().";
}
TEST_F(TestingAssignmentOperator, TestAssigmentOperatorModelSet) {
    EXPECT_EQ(baseSimplexPoint.modelIsSet(), testingPoint.modelIsSet()) << "ModelSet flag was not copied correctly using modelIsSet().";
}
TEST_F(TestingAssignmentOperator, TestAssigmentOperatorErrorModelSet) {
    EXPECT_EQ(baseSimplexPoint.errorModelIsSet(), testingPoint.errorModelIsSet()) << "ErrorModelSet flag was not copied correctly using errorModelIsSet().";
}
TEST_F(TestingAssignmentOperator, TestAssigmentOperatorModel) {
    // Note: Direct comparison of shared_ptrs. If you need to compare the underlying objects, you might need a custom method or logic.
    EXPECT_EQ(baseSimplexPoint.getModel(), testingPoint.getModel()) << "Model shared_ptr was not copied correctly using getModel().";
}
TEST_F(TestingAssignmentOperator, TestAssigmentOperatorErrorModel) {
    // Note: Direct comparison of shared_ptrs. If comparing the underlying objects is needed, consider adding a method for that purpose.
    EXPECT_EQ(baseSimplexPoint.getErrorModel(), testingPoint.getErrorModel()) << "ErrorModel shared_ptr was not copied correctly using getErrorModel().";
}
TEST_F(TestingAssignmentOperator, TestAssigmentOperatorError) {
    EXPECT_DOUBLE_EQ(baseSimplexPoint.getError(), testingPoint.getError()) << "Error value was not copied correctly using getError().";
}
}
//* testing assignment operator
