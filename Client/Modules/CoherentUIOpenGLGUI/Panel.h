#pragma once

#include "HTMLElement.h"

#include <ClientBase/IPanel.h>

namespace CoherentUIOpenGLUI {
	class PanelGenerator final : public GUI::IPanelGenerator {
	public:
		void Generate(std::ostream &output);

	protected: // Internal Generation Helpers
		virtual HTMLElement GenerateHTML();
	};
}