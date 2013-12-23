#pragma once

namespace Core { class Engine; }

namespace StateEngine {
	class IState {
	public:
		virtual ~IState() {}

		virtual void Update(const float delta) = 0;
		virtual void Render(const float delta) = 0;
	};

	// These two classes wrap around a State to provide a factory for async state initialization
	// At compile time it basically creates separate classes implementing IStateFactory for every
	// State that's being switched to at some point.

	// Abstract State Factory Class
	class IStateFactory {
	public:
		virtual ~IStateFactory() {}
		virtual IState* New(Core::Engine &engine) = 0;
	};
	
	// State Factory Class
	template<class T> class StateFactory final : public IStateFactory {
	public:
		IState* New(Core::Engine &engine) { return new T(engine); }
	};
}