#include "SelectionRenderer.h"

#include <ClientBase/BaseUnitTypes.h>

#include "GLheaders.h"

#include <cmath>

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	SelectionRenderer::SelectionRenderer()
	{}

	// Rendering Functions
	void SelectionRenderer::RenderSelectionBoxes(const std::list<std::unique_ptr<Tools::Units::IUnit>> &units) {
		for (const std::unique_ptr<Tools::Units::IUnit> &unit : units) {
			glPushMatrix();

			// Translate to Position
			glTranslated(unit->GetPosition().x, unit->GetPosition().y, 0);

			// Render Line Loop
			glBindTexture(GL_TEXTURE_2D, NULL);
			glLineWidth(1.5f);
			glLineStipple(7, 0xAAAA);
			glColor4f(0.1f, 0.1f, 0.1f, 0.8f);

			glBegin(GL_LINE_LOOP);
			for (float i = 0; i <= (float)M_PI * 2.0f; i += (float)M_PI / 8.0f)
				glVertex2f(cos(i) * 0.38f, sin(i) * 0.38f);
			glEnd();

			// Clean Up
			glColor3f(1.0f, 1.0f, 1.0f);

			glPopMatrix();
		}
	}
}