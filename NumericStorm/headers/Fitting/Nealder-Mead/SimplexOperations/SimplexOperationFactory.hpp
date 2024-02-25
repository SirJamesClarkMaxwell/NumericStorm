#pragma once
#include <unordered_map>
#include <string>
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
#include "NoAvailableFactoryException.hpp"

// TODO: we need to redefine this methods, operator should receive the SimplexFigure argument and as a member variable should hold the SimplexOperationArgument, and this should be a probably a sharedPointer
// TODO: redefine interface of SimplexOperation

namespace NumericStorm
{
	namespace Fitting
	{
		template <size_t figure_size>
		class SimplexOperationFactory
		{
		public:
			SimplexOperationFactory(){};
			void registerOperation(std::string operationName, ISimplexOperation<figure_size> operation);
			void unRegisterOperation(std::string operatioName) throw NoAvailableFactoryException;
			ISimplexOperation<figure_size> createOperation(std::string name, SimplexOperationArguments additionalArguments) throw NoAvailableFactoryException;

		private:
			std::unordered_map<std::string, ISimplexOperation<figure_size>> m_listOperation;
		};

		template <size_t figure_size>
		void SimplexOperationFactory<figure_size>::registerOperation(std::string operationName,
																	 ISimplexOperation<figure_size> operation)
		{
			m_listOperation[operationName] = operation;
		}

		template <size_t figure_size>
		void SimplexOperationFactory<figure_size>::unRegisterOperation(std::string operatioName)
		{
			if !(m_listOperation.erase(operatioName))
				throw NoAvailableFactoryException(operatioName);
		}

		template <size_t figure_size>
		ISimplexOperation<figure_size> SimplexOperationFactory<figure_size>::createOperation(std::string operationName, SimplexOperationArguments additionalArguments)
		{
#if DEBUG
			if (true)
			{
				ISimplexOperation<figure_size> operationObject = m_listOperation[operationName];
				auto &toReturn = operationObject(additionalArguments);
				return toReturn;
			}
			else
				throw NoAvailableFactoryException(operationName)
#endif
					return m_listOperation[operationName](additionalArguments);
		}

	}
}