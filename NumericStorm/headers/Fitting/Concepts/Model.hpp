#pragma once
#include <concepts>
#include <cstddef>

#include "Data.hpp"
#include "Parameters.hpp"



namespace NumericStorm::Concepts {
	using namespace NumericStorm::Fitting;

	template <class M>
	concept Model = requires(M model,
		Data & data,
		const Parameters<M::parameter_size>&parameters,
		const typename M::AuxParameters & auxParams) {
		{ M::parameter_size } -> std::same_as<const size_t>;
		typename M::AuxParameters;
		{ model(data, parameters, auxParams) } -> std::same_as<void>;
	};
}

