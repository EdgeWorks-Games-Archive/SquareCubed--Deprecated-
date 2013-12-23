#pragma once

namespace Graphics {
	class ITexture2D;

	class ITileArray {
	public: // Initialization/Uninitialization
		virtual ~ITileArray() {}

	public: // Texture Utility Functions
		virtual ITexture2D& GetTexture(unsigned int index) = 0;
	};
}