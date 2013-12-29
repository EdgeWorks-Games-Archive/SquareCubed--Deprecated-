#pragma once

#include <ClientBase/ICamera.h>

#include <CommonLib/postypes.h>

namespace OpenGLGraphics {
	class OpenGLCamera : public Graphics::ICamera {
		float m_AspectRatio;
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::ivec2 m_Resolution;

	public:
		OpenGLCamera() :
			// Default Values
			m_Position(),
			m_Size(),
			m_Resolution(),
			// Can't have the aspect ratio at weird values, might cause problems
			m_AspectRatio(1)
		{}

		OpenGLCamera(glm::ivec2 resolution)
			: OpenGLCamera()
		{
			SetResolution(resolution);
		}

		void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		void SetResolution(glm::ivec2 resolution) {
			m_Resolution = std::move(resolution);
			m_AspectRatio = (float) m_Resolution.x / (float) m_Resolution.y;
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

		glm::vec2 ResolveWorldPosition(const glm::vec2 &absolute) {
			glm::vec2 retVal = glm::vec2(m_Position.x, m_Position.y);
			// TODO: improve to not divide every time used
			retVal.x += m_Size.x * (absolute.x / m_Resolution.x);
			retVal.y += m_Size.y * (absolute.y / m_Resolution.y);
			return retVal;
		}
	};
}