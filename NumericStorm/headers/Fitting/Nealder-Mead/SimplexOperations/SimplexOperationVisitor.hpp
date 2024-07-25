#pragma once

#include "OperationList.hpp"
#include "SimplexOperationBase.hpp"
#include "Visitor.hpp"

namespace NumericStorm::Fitting {
using namespace NumericStorm::Concepts;

	template <size_t parameter_size, OperationList List>
	class SimplexOperationVisitor : public Visitor<List, SimplexOperationBase<parameter_size>> {};
};