#pragma once

namespace NumericStorm::Utils
{
	template <typename... Ts>
	struct type_list
	{
		using get_variant = std::variant<Ts...>;

	};

	template<typename List>
	struct pop_front;

	template<typename Head, typename... Tail>
	struct pop_front<type_list<Head, Tail...>>
	{
		using out = Head;
		using type = type_list<Tail...>;
	};

	template<typename List>
	using pop_front_t = pop_front<List>::type;

	template<typename List>
	using pop_front_o = pop_front<List>::out;

}