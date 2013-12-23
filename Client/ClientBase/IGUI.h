#pragma once

#include <string>

namespace GUI {
	class IGUIBindings;

	class IGUI {
	public: // Initialization/Uninitialization
		virtual ~IGUI() {}

	public: // Utility Functions
		virtual void SwitchView(std::wstring view) = 0;
		virtual IGUIBindings& GetBindings() = 0;

	public: // Game Loop
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}