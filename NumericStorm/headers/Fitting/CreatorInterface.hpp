#pragma once

namespace NumericStorm {
namespace Fitting {
	template<class CreatorInput, class CreatorOutput, class CreatorSettings>
	class CreatorInterface {
	public:
		using In = CreatorInput;
		using Out = CreatorOutput;
		using Settings = CreatorSettings;


		CreatorInterface() = default;
		CreatorInterface(const CreatorInterface<In, Out, Settings>&) = default;
		CreatorInterface(CreatorInterface<In, Out, Settings>&&) = default;
		CreatorInterface<In, Out, Settings>& operator=(const CreatorInterface<In, Out, Settings>&) = default;
		CreatorInterface<In, Out, Settings>& operator=(CreatorInterface<In, Out, Settings>&&) = default;

		virtual ~CreatorInterface() = default;

		virtual Out operator()(In) = 0;
		virtual void updateSettings(const Settings& settings) { m_settings = settings; }

	protected:
		Settings m_settings{};

	};
}
}