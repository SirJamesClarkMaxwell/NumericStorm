#pragma once
namespace NumericStorm
{
namespace Fitting
{

template<size_t parameter_size>
class AdditionalParameters
{
public:
	AdditionalParameters() = default;
	virtual ~AdditionalParameters() = default;
	Parameters<parameter_size> getMinBounds() const { return m_minBounds; }
	Parameters<parameter_size> getMaxBounds() const { return m_maxBounds; }
protected:
	Parameters<parameter_size> m_minBounds{};
	Parameters<parameter_size> m_maxBounds{};
};
}

}