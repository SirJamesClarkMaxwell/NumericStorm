#pragma once



namespace NumericStorm::Concepts {
template <typename T>
concept OperationSettings = requires {
	typename T::In;
	typename T::Out;
};
}