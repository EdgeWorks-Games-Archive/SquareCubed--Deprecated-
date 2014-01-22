#pragma once

#include "Element.h"

#include <ClientBase/IProgressBar.h>

namespace CoherentUIOpenGLUI {
	class ProgressBarGenerator final : public virtual GUI::Elements::IProgressBarGenerator, public ElementGenerator {
	protected: // Internal Generation Helpers
		virtual HTMLElement GenerateHTML();
	};
}