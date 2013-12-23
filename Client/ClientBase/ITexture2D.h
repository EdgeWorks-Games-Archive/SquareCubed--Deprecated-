#pragma once

namespace Graphics {
	class ITexture2D {
	public: // Initialization/Uninitialization
		virtual ~ITexture2D() {}

	public: // Render Functions
		virtual void Render(float x, float y, float w, float h) = 0;
	};
}