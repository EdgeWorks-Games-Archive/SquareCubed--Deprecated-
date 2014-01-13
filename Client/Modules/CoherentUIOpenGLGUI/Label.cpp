#include "Label.h"

namespace CoherentUIOpenGLUI {
	LabelGenerator::LabelGenerator(std::string text) :
		m_Text(std::move(text))
	{}

	void LabelGenerator::Generate(std::ofstream &file) {
		file << "<p>" << m_Text << "</p>\n";
	}
}