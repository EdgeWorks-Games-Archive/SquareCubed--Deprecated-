#pragma once

namespace Context { class IWindow; }
namespace Graphics { class IGraphics; }

namespace OpenGLGraphics {
	// Use this function to create a new OpenGLGraphics object without
	// including OpenGLGraphics.h (and the includes that come with it)
	Graphics::IGraphics* LoadGraphics(Context::IWindow &window, Content::Content &content);
}