#include "SelectionRenderer.h"

#include <ClientBase/BaseUnitTypes.h>

#include "GLheaders.h"

#include <cmath>

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	SelectionRenderer::SelectionRenderer()
	{}

	// Rendering Functions

	void SelectionRenderer::RenderUnitSelection(const std::list<std::unique_ptr<Tools::Units::IUnit>> &units) {
		for (const std::unique_ptr<Tools::Units::IUnit> &unit : units) {
			glPushMatrix();

			// Translate to Position
			glTranslatef(unit->GetPosition().x, unit->GetPosition().y, 0);

			// Prepare for Rendering
			glBindTexture(GL_TEXTURE_2D, NULL);
			glLineWidth(1.5f);
			glLineStipple(7, 0xAAAA);
			glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
			glEnable(GL_LINE_STIPPLE);

			// Render Line Loop
			glBegin(GL_LINE_LOOP);
			for (float i = 0; i < (float)M_PI * 2.0f; i += (float)M_PI / 8.0f)
				glVertex2f(cos(i) * 0.38f, sin(i) * 0.38f);
			glEnd();

			// Clean Up
			glColor3f(1.0f, 1.0f, 1.0f);
			glDisable(GL_LINE_STIPPLE);

			glPopMatrix();
		}
	}

	void SelectionRenderer::RenderSelectionBox(const glm::vec2 &bottomLeft, const glm::vec2 &size) {
		glPushMatrix();

		// Translate to Bottom Left
		glTranslatef(bottomLeft.x, bottomLeft.y, 0);

		// Prepare for Rendering
		glBindTexture(GL_TEXTURE_2D, NULL);
		glLineWidth(1.0f);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		// Render Square Lines
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 0);
		glVertex2f(0, size.y);
		glVertex2f(size.x, size.y);
		glVertex2f(size.x, 0);
		glEnd();

		// Clean Up
		glColor3f(1.0f, 1.0f, 1.0f);

		glPopMatrix();
	}
}