#pragma once

#include <functional>

#include "Data.hpp"

namespace NumericStorm::Fitting {

	class ErrorModel {

	public:
		ErrorModel(std::function<double(const Data&, const Data&)> errorModel)
			: m_errorModel{ errorModel } {}
	
		virtual ~ErrorModel() = default;
	
		double operator()(const Data& referencedData, const Data& comparedData) const {
			double error = m_errorModel(referencedData, comparedData);
		}
	
		auto getErrorModel() const {
			return m_errorModel;
		}
	
		void setErrorModel(std::function<double(const Data&, const Data&)> errorModel) {
			m_errorModel = errorModel;
		}
	
		bool isModelValid() const {
			return m_errorModel != nullptr;
		}
	
	protected:
		std::function<double(const Data&, const Data&)> m_errorModel;
	};
}
