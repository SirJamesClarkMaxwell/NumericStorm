#pragma once

#include <unordered_map>
#include <vector>

#include "type_list.hpp"
#include "OperationList.hpp"
#include "OperationBase.hpp"

namespace NumericStorm::Fitting
{
	using namespace NumericStorm::Concepts;
	using namespace NumericStorm::Utils;
	
	template<OperationList List, OperationBase Base = pop_front_o<List>>
	class Visitor {
	public:
	
	
		virtual ~Visitor() = default;
	
	
		typename Base::Out visit(typename List::operations_e operation, typename Base::In& input);
	
		void updateSettings(typename List::operations_e operation, const Base::SettingsT& newSettings);
	
		using registerInputT = std::pair<typename List::operations_e, typename Base::SettingsT>;
	
		void registerOperations(const std::vector<registerInputT>& settingsVector)
		{
			registerOperations<List::list>(0, settingsVector);
		};
	
	
	protected:
		std::unordered_map<typename List::operations_e, typename List::variant_t> m_operationList{};
	
	private:
		template<typename oplist>
		void registerOperations(size_t position, const std::vector<registerInputT>& input)
		{
			if (position >= input.size())
				return;
			registerOneOperation<pop_front_o<oplist>>(input[position]);
			registerOperations<pop_front_t<oplist>>(position + 1, input);
		};
	
		template<class Op>
		void registerOneOperation(const registerInputT& input)
		{
			Op instance{ input.second() };
			m_operationList[input.first()] = instance;
		}
	
	
		bool hasOperation(List::operation_e operation) const
		{
			return m_operationList.contains(operation);
		}
	};
	
	template<OperationList List, OperationBase Base>
	typename Base::Out Visitor<List, Base>::visit(typename List::operations_e operation, typename Base::In& input) {
	
		return std::visit([&input](auto&& operation) { return operation(input); }, m_operationList[operation]);
	
	};
	template<OperationList List, OperationBase Base>
	void Visitor<List, Base>::updateSettings(typename List::operations_e operation, const Base::SettingsT& newSettings) {
		
		if (hasOperation(operation))
			std::visit([&newSettings](auto&& operation) { operation.updateSettings(newSettings); }, m_operationList[operation]);
	
	};
}