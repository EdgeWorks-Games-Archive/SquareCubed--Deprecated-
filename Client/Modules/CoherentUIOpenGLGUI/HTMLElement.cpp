#include "HTMLElement.h"

#include <sstream>

namespace CoherentUIOpenGLUI {
	void HTMLHelper::Escape(std::string &data) {
		std::string::size_type pos = 0;
		while (true) {
			pos = data.find_first_of("\"&<>", pos);
			if (pos == std::string::npos) break;
			std::string replacement;
			switch (data[pos]) {
			case '\'': replacement = "&apos;"; break;
			case '\"': replacement = "&quot;"; break;
			case '&':  replacement = "&amp;";  break;
			case '<':  replacement = "&lt;";   break;
			case '>':  replacement = "&gt;";   break;
			default:;
			}
			data.replace(pos, 1, replacement);
			pos += replacement.size();
		};
	}

	HTMLElement::HTMLElement(std::string tag) :
		m_StyleEntries(),
		Tag(std::move(tag)),
		Content(),
		ID()
	{}

	void HTMLElement::Generate(std::ostream &output) {
		// Add Opening Tag
		output << "<" << Tag;
		if (ID != "") output << " id=\"" << ID << "\"";
		// If there's style entries, add those
		if (!m_StyleEntries.empty()) {
			output << " style=\"";
			for (std::string &entry : m_StyleEntries)
				output << entry;
			output << "\"";
		}
		output << ">";

		// Add Content and Closing Tag
		output << Content << "</" << Tag << ">";
	}
}