#pragma once
#include "NumericStorm.hpp"
#include "../pch.h"
#include "../FittingTestsSetUp.hpp"
using namespace NumericStorm::Fitting;

struct OperationFactoryTest : public ::testing::Test
{
    OperationFactoryTest() {
		std::shared_ptr<Data> data_ptr = std::make_shared<Data>(objs.true_datum);

		referenceFigure[0] = SimplexPoint<4>{ data_ptr, objs.evaluatedArray };

		//referenceFigure[0].onEvaluate([&](SimplexPoint<4>& point) {
			//point.evaluatePoint(objs.gModel, objs.eModel, objs.additionalParameters);
		//});

		std::function<void(SimplexPoint<4>&)> f = std::bind(&OperationFactoryTest::evalCallback, this, std::placeholders::_1);
		

		referenceFigure[0].onEvaluate(f);

		referenceFigure[0].evaluatePoint();
		for (int i = 1; i < 5; i++) {
			referenceFigure[i] = SimplexPoint<4>{ referenceFigure[0] };
			referenceFigure[i][i - 1] += 1;
			referenceFigure[i].evaluatePoint();
		}
		referenceFigure.sort();

		testedFigure = referenceFigure;

		registerAllOperations();
    };
   
    void SetUp() {

    }
	void evalCallback(SimplexPoint<4>& point) {
		point.evaluatePoint(objs.gModel, objs.eModel, objs.additionalParameters);
	}
    void registerAllOperations() {
		opFactory.registerCreators<Reflection<4>, Expansion<4>, Contraction<4>, Shrinking<4>>(setupInfo);
    }

    UsefulObjects objs{};
    SimplexFigure<4> testedFigure{};
    SimplexFigure<4> referenceFigure{};
	

	SimplexOperationFactory<4> opFactory{};
	

	std::vector<CreatorSetUpInfo<SimplexOperationSettings>> setupInfo{
		{"reflection", 1.5},
		{"expansion", 0.5},
		{"contraction", 2.0},
		{"shrinking", 0.5}
	};

    Reflection<4> reflOp{ 1.5 };
    Expansion<4> expOp{ 0.5 };
    Contraction<4> contOp{ 2.0 };
    Shrinking<4> shOp{ 0.5 };
};
