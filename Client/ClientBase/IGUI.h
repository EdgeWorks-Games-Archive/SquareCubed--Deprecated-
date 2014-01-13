#pragma once

#include "Types.h"

#include <string>
#include <memory>

namespace GUI {
	class IGUI {
	public: // Initialization/Uninitialization
		virtual ~IGUI() {}

	public: // Utility Functions
		/** Switches to a view at this path. In the process of being replaced. */
		virtual void SwitchView(std::wstring view) = 0;
		/** Returns the bindings helper class. In the process of being replaced. */
		virtual IGUIBindings& GetBindings() = 0;

	public: // View Helpers
		virtual std::unique_ptr<IViewGenerator> CreateViewGenerator() = 0;
		virtual void SwitchView(IView &view) = 0;

	public: // Game Loop
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}