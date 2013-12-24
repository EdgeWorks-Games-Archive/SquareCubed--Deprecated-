#pragma once

#include <ClientBase/ICamera.h>

#include <CommonLib/postypes.h>

namespace OpenGLGraphics {
	class OpenGLCamera : public Graphics::ICamera {
		float m_AspectRatio;
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec3 m_Rotation;

	public:
		OpenGLCamera() :
			// Default Values
			m_Position(),
			m_Size(),
			m_Rotation(),
			// Can't have the aspect ratio at weird values, might cause problems
			m_AspectRatio(1)
		{}

		OpenGLCamera(glm::ivec2 resolution)
			: OpenGLCamera()
		{
			SetAspectRatioByResolution(resolution);
		}

		void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		void SetAspectRatioByResolution(glm::ivec2 resolution) {
			m_AspectRatio = (float) resolution.x / (float) resolution.y;
		}
		double GetAspectRatio() { return m_AspectRatio; }

		void SetPosition(float x, float y, float z) { m_Position.x = x; m_Position.y = y; m_Position.z = z; }
		void SetPosition(glm::vec3 position) { m_Position = position; }
		void SetPosition(float x, float y) { m_Position.x = x; m_Position.y = y; }
		void SetPosition(glm::vec2 position) { m_Position.x = position.x; m_Position.y = position.y; }
		glm::vec3& GetPosition() { return m_Position; }

		void SetWidth(float width) {
			m_Size.x = width;
			m_Size.y = width / m_AspectRatio;
			OnResize.Invoke(Utils::NO_ARGS);
		}
		void SetHeight(float height) {
			m_Size.x = height * m_AspectRatio;
			m_Size.y = height;
			OnResize.Invoke(Utils::NO_ARGS);
		}
		glm::vec2& GetSize() { return m_Size; }

		void SetRotation(float x, float y, float z) { m_Rotation.x = x; m_Rotation.y = y; m_Rotation.z = z; }
		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
		glm::vec3& GetRotation() { return m_Rotation; }
	};
}