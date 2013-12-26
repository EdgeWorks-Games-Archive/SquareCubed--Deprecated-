#pragma once

#include <string>

namespace Graphics {
	class ITileRenderer;
	class IUnitRenderer;
	class ISelectionRenderer;

	class ITexture2D;
	class ITileArray;

	class IGraphicsFactory {
	public:
		virtual ~IGraphicsFactory() {}

	public: // Renderer Types
		virtual ITileRenderer* CreateTileRenderer(ITileArray &tileArray) = 0;
		virtual IUnitRenderer* CreateUnitRenderer(ITileArray &tileArray) = 0;
		virtual ISelectionRenderer* CreateSelectionRenderer() = 0;

	public: // Content Types
		/// <summary>Gets or creates a 2D texture associated with the path.</summary>
		/// <returns>Returns a reference to the ITexture2D assocaited with the path.</returns>
		virtual ITexture2D& GetTexture2D(const std::string &path) = 0;

		/// <summary>Gets or creates a tile array associated with the path.</summary>
		/// <returns>Returns a reference to the ITileArray assocaited with the path.</returns>
		virtual ITileArray& GetTileArray(const std::string &path) = 0;
	};
}