#pragma once

#include <type_traits>
#include <variant>

#include "type_list.hpp"
#include "Operation.hpp"

namespace NumericStorm::Concepts
{
    using namespace NumericStorm::Utils;

    template <typename T>
    struct is_std_variant : std::false_type {};
    
    template <typename... Args>
    struct is_std_variant<std::variant<Args...>> : std::true_type {};
    
    template <typename T>
    constexpr bool is_std_variant_v = is_std_variant<T>::value;

    template<typename T>
    struct is_type_list : std::false_type {};

    template<typename... Ts>
    struct is_type_list<Utils::type_list<Ts...>> : std::true_type {};

    template<typename T>
    constexpr bool is_type_list_v = is_type_list<T>::value;

    template<typename TypeList>
    struct all_operation : std::false_type {};

    template<Operation... Types>
    struct all_operation<type_list<Types...>> : std::true_type {};

    template<typename TypeList>
    constexpr bool all_operation_v = all_operation<TypeList>::value;
    

    template <typename T>
    concept OperationList = requires {
        typename T::operations_e;
        typename T::variant_t;
        typename T::list;
    
            requires std::is_enum_v<typename T::operations_e>;
            requires is_std_variant_v<typename T::variant_t>;
            requires all_operation_v<typename T::list>;
    };
}