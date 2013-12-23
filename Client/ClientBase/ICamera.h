#pragma once

#include <CommonLib/postypes.h>
#include <CommonLib/Events.h>

namespace Graphics {
	class ICamera {
	public:
		virtual ~ICamera() {}

	public: // Events
		Utils::Event<Utils::EmptyEventArgs> OnResize;

	public: // Position Accessors
		/// <summary>Sets the Position</summary>
		/// <param name="x">X Coordinate</param>
		/// <param name="y">Y Coordinate</param>
		/// <param name="z">Z Coordinate</param>
		virtual void SetPosition(float x, float y, float z) = 0;

		/// <summary>Sets the Position</summary>
		/// <param name="position">The new Position</param>
		virtual void SetPosition(glm::vec3 position) = 0;

		/// <summary>Sets the Position</summary>
		/// <param name="x">X Coordinate</param>
		/// <param name="y">Y Coordinate</param>
		virtual void SetPosition(float x, float y) = 0;

		/// <summary>Sets the Position</summary>
		/// <param name="position">The new Position</param>
		virtual void SetPosition(glm::vec2 position) = 0;

		/// <summary>Gets the Position</summary>
		/// <returns>Reference to the Position</returns>
		virtual glm::vec3& GetPosition() = 0;

	public: // Size Accessors
		/// <summary>Gets the Size</summary>
		/// <returns>Reference to the Size</returns>
		virtual glm::vec2& GetSize() = 0;

	public: // Size Helper Functions
		/// <summary>Sets the height and calculates the width using the aspect ratio.</summary>
		/// <param name="height">The new Height</param>
		virtual void SetHeight(float height) = 0;

		/// <summary>Sets the width and calculates the height using the aspect ratio.</summary>
		/// <param name="width">The new Width</param>
		virtual void SetWidth(float width) = 0;
	};
}