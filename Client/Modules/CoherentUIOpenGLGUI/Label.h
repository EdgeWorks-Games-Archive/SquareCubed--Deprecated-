#pragma once

#include <ClientBase/ILabel.h>

#include <memory>

namespace CoherentUIOpenGLUI {
	/// Static Label ///

	class LabelGenerator : public virtual GUI::ILabelGenerator {
	public:
		virtual ~LabelGenerator();

		void Generate(std::ostream &output);
	};

	/// Dynamic Label ///

	class DynamicLabel : public GUI::IDynamicLabel {
	public:
		void SetText(std::string text);
	};

	class DynamicLabelGenerator : public GUI::IDynamicLabelGenerator, public LabelGenerator {
	public:
		DynamicLabelGenerator(std::unique_ptr<GUI::IDynamicLabel> &bindingObject);
	};
}