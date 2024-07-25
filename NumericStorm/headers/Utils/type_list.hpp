#pragma once
#include <variant>

namespace NumericStorm::Utils
{
	template <class... Ts>
	struct type_list
	{
		using get_variant = typename std::variant<Ts...>;

	};

	template<class List>
	struct pop_front;

	template<class Head, class... Tail>
	struct pop_front<type_list<Head, Tail...>>
	{
		using out = Head;
		using type = type_list<Tail...>;
	};

	template<class List>
	using pop_front_t = pop_front<List>::type;

	template<class List>
	using pop_front_o = pop_front<List>::out;

}