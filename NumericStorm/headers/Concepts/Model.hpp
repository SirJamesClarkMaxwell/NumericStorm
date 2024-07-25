#pragma once
#include <concepts>
#include <cstddef>

#include "Data.hpp"
#include "Parameters.hpp"



namespace NumericStorm::Concepts {
	using namespace NumericStorm::Fitting;

	template <typename M>
	concept Model = requires(M model,
		Data & data,
		const Parameters<M::parameter_size>&parameters,
		const typename M::AuxParameters & auxParams) {
		typename M::parameter_size;
		typename M::AuxParameters;
		{ model(data, parameters, auxParams) } -> std::same_as<void>;
	};
}

