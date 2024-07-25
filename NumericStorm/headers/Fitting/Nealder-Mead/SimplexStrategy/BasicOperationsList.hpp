#pragma once

#include "type_list.hpp"
#include "Reflection.hpp"
#include "Expansion.hpp"
#include "Contraction.hpp"
#include "Shrinking.hpp"

#include "BasicOperationsEnum.hpp"


namespace NumericStorm::Fitting {
using namespace NumericStorm::Utils;


	template<size_t parameter_size>
	struct BasicOperationsList {
		using list = type_list<Reflection<parameter_size>, 
							Expansion<parameter_size>,
							Contraction<parameter_size>,
							Shrinking<parameter_size>>;

		using operations_e = BasicOperationsEnum;
		using variant_t = typename list::get_variant;
	};
};
