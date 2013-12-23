#pragma once

namespace Graphics {
	class ICamera;
	class IGraphicsFactory;

	/// <summary>
	/// Implementations of IGraphics are responsible for managing
	/// Graphics-related functionality.
	/// </summary>
	class IGraphics {
	public: // Initialization/Uninitialization
		virtual ~IGraphics() {}

	public: // Property Accessors
		/// <summary>Gets the Main Camera</summary>
		/// <returns>Reference to the Main Camera</returns>
		virtual ICamera& GetMainCamera() = 0;

	public: // Utility Functions
		/// <summary>
		/// Gets the <see cref="Graphics::IGraphicsFactory">IGraphicsFactory</see> for this instance.
		/// </summary>
		/// <returns>Returns the graphics factory.</returns>
		virtual IGraphicsFactory& GetFactory() = 0;

		virtual void Push() = 0;
		virtual void Pop() = 0;
		virtual void Translate(double x, double y) = 0;
		virtual void TranslateLayer(double z) = 0;
		virtual void Rotate(float rot) = 0;
		virtual void Flush() = 0;

		/// <summary>Renders a Test Triangle</summary>
		virtual void RenderTest() = 0;

	public: // Game Loop
		/// <summary>Prepares the Engine for Rendering</summary>
		virtual void BeginRender() = 0;
		/// <summary>Prepares the Engine for GUI Rendering</summary>
		virtual void BeginGUIRender() = 0;
		/// <summary>Finishes ALL Rendering</summary>
		virtual void EndRender() = 0;
	};
}