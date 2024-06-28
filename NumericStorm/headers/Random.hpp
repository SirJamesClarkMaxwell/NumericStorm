#pragma once

#include <random>

namespace NumericStorm {
class Random
{
public:


	static uint32_t UInt()
	{
		std::random_device s_Device;
		std::mt19937 s_RandomEngine{ s_Device() };
		std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
		return s_Distribution(s_RandomEngine);
	}

	static uint32_t UInt(uint32_t min, uint32_t max)
	{
		std::random_device s_Device;
		std::mt19937 s_RandomEngine{ s_Device() };
		std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
		return min + (s_Distribution(s_RandomEngine) % (max - min + 1));
	}

	static float Float(double min, double max)
	{
		std::random_device s_Device;
		std::mt19937 s_RandomEngine{ s_Device() };
		std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;

		double factor = (max - min) + min;
		return (float)factor * s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}

};

}