#pragma once

#include "Element.h"

#include <ClientBase/ILabel.h>

#include <memory>

namespace CoherentUIOpenGLUI {
	class ViewEventListener;

	/// Static Label ///

	class LabelGenerator : public virtual GUI::Elements::ILabelGenerator, public ElementGenerator {
	public:
		virtual ~LabelGenerator();
		void Generate(std::ostream &output);

	protected: // Internal Generation Helpers
		virtual HTMLElement GenerateHTML();
	};

	/// Dynamic Label ///

	class DynamicLabel final : public GUI::Elements::IDynamicLabel {
		ViewEventListener &m_ViewListener;
		std::string m_HTMLId;

	public:
		DynamicLabel(ViewEventListener &viewListener, std::string htmlId);
		void SetText(std::string text);
	};

	class DynamicLabelGenerator final : public GUI::Elements::IDynamicLabelGenerator, public LabelGenerator {
		static unsigned int nextId;
		ViewEventListener &m_ViewListener;

	public: // Properties
		const unsigned int ID;
		std::unique_ptr<GUI::Elements::IDynamicLabel> &BindingObject;

	public:
		DynamicLabelGenerator(ViewEventListener &viewListener, std::unique_ptr<GUI::Elements::IDynamicLabel> &bindingObject);
		void Generate(std::ostream &output);

	protected: // Internal Generation Helpers
		virtual HTMLElement GenerateHTML();
	};
}