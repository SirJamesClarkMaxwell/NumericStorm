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
#if !defined(JFM_PLATFORM_NIX)
		using out = typename Head;
		using type = typename type_list<Tail...>;
#else
		using out = Head;
		using type = type_list<Tail...>;
#endif
	};

	template<>
	struct pop_front<type_list<>>
	{
		using out = type_list<>;
		using type = type_list<>;
	};

	template<class List>
	using pop_front_t = typename pop_front<List>::type;

	template<class List>
	using pop_front_o = typename pop_front<List>::out;

}
