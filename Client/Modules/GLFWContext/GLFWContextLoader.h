#pragma once

namespace Context { class IContext; }

namespace GLFWContext {
	// Use this function to create a new GLFWGraphics object without
	// including GLFWGraphics.h (and the includes that come with it)
	Context::IContext* LoadContext();
}