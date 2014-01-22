#include "UnitRenderer.h"

#include <ClientBase/ITileArray.h>
#include <ClientBase/ITexture2D.h>
#include <ClientBase/BaseUnitTypes.h>

#include "GLheaders.h"

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	UnitRenderer::UnitRenderer(Graphics::ITileArray &tileTextures) :
		m_TileTextures(tileTextures)
	{}

	// Rendering Functions
	void UnitRenderer::RenderUnits(const std::list<std::unique_ptr<Tools::Units::IUnit>> &units) {
		for (const std::unique_ptr<Tools::Units::IUnit> &unit : units) {
			glPushMatrix();

			// Render Unit Graphic
			glTranslated(unit->GetPosition().x, unit->GetPosition().y, 0);
			glPushMatrix();
			glRotatef(unit->GetRotation().GetDegrees(), 0, 0, 1);
			m_TileTextures.GetTexture(unit->GraphicID).Render(-0.4f, -0.4f, 0.8f, 0.8f);
			glPopMatrix();

			if (unit->Health.Current != unit->Health.Max) {
				// Calculate Health Bar Location and Size
				// TODO: Precalculate inverse max health
				float invMax = 1.0f / unit->Health.Max;
				float w = invMax * 0.8f * unit->Health.Current;

				// Prepare to Render
				glBindTexture(GL_TEXTURE_2D, NULL);

				// Render Health Bar Background
				glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
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