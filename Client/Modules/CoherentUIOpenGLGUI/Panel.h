#pragma once

#include "HTMLElement.h"

#include <ClientBase/IPanel.h>

#include <list>

namespace CoherentUIOpenGLUI {
	class PanelGenerator final : public GUI::Elements::IPanelGenerator {
		std::list<std::unique_ptr<GUI::Elements::IElementGenerator>> m_ElementGenerators;

	public:
		void Generate(std::ostream &output);

	protected: // Internal Generation Helpers
		virtual HTMLElement GenerateHTML();

	public: // Adding Subcomponents
		void Add(std::unique_ptr<GUI::Elements::IElementGenerator> element);
	};
}