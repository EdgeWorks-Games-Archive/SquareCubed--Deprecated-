#pragma once

#include "HTMLElement.h"

#include <ClientBase/IElement.h>

namespace CoherentUIOpenGLUI {
	class ElementGenerator : public virtual GUI::Elements::IElementGenerator {
	public:
		virtual ~ElementGenerator() {}

	public: // Generation
		virtual void Generate(std::ostream &output);

	protected: // Internal Generation Helpers
		virtual HTMLElement GenerateHTML();
	};
}