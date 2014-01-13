#pragma once

#include <ClientBase/ILabel.h>

#include <string>

namespace CoherentUIOpenGLUI {
	class LabelGenerator final : public GUI::ILabelGenerator {
		std::string m_Text;

	public:
		LabelGenerator(std::string text);
		void Generate(std::ofstream &file);
	};
}