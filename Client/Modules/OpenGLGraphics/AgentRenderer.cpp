#include "AgentRenderer.h"

#include <ClientBase/ITileArray.h>
#include <ClientBase/ITexture2D.h>
#include <ClientBase/BaseAgentTypes.h>

#include "GLheaders.h"

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	AgentRenderer::AgentRenderer(Graphics::ITileArray &tileTextures) :
		m_TileTextures(tileTextures)
	{}

	// Rendering Functions
	void AgentRenderer::RenderAgents(const std::list<std::unique_ptr<Tools::Agents::IAgent>> &agents) {
		for (const std::unique_ptr<Tools::Agents::IAgent> &agent : agents) {
			glPushMatrix();

			// Render Agent Graphic
			glTranslated(agent->GetPosition().x, agent->GetPosition().y, 0);
			glPushMatrix();
			glRotatef(agent->GetRotation().GetDegrees(), 0, 0, 1);
			m_TileTextures.GetTexture(agent->GraphicID).Render(-0.4f, -0.4f, 0.8f, 0.8f);
			glPopMatrix();

			if (agent->Health.Current != agent->Health.Max) {
				// Calculate Health Bar Location and Size
				// TODO: Precalculate inverse max health
				float invMax = 1.0f / agent->Health.Max;
				float w = invMax * 0.8f * agent->Health.Current;

				// Prepare to Render
				glBindTexture(GL_TEXTURE_2D, NULL);

				// Render Health Bar Background
				glColor4f(0.2f, 0.2f, 0.2f, 0.8f);
				glBegin(GL_QUADS);
				glVertex2f(-0.4f, 0.3f);
				glVertex2f(-0.4f + 0.8f, 0.3f);
				glVertex2f(-0.4f + 0.8f, 0.3f + 0.05f);
				glVertex2f(-0.4f, 0.3f + 0.05f);
				glEnd();

				// Render Health Bar Foreground
				glColor3f(0.8f, 0.0f, 0.0f);
				glBegin(GL_QUADS);
				glVertex2f(-0.4f, 0.3f);
				glVertex2f(-0.4f + w, 0.3f);
				glVertex2f(-0.4f + w, 0.3f + 0.05f);
				glVertex2f(-0.4f, 0.3f + 0.05f);
				glEnd();

				// Clean Up
				glColor3f(1.0f, 1.0f, 1.0f);
			}

			glPopMatrix();
		}
	}
}