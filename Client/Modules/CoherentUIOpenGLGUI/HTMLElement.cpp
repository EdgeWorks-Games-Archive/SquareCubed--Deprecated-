#include "HTMLElement.h"

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
		Tag(std::move(tag))
	{}

	void HTMLElement::Generate(std::ostream &output) {
		// Add Opening Tag
		output << "<" << Tag;
		if (ID != "") output << " id=\"" << ID << "\"";
		if (Style != "") output << " style=\"" << Style << "\"";
		output << ">";

		// Add Content and Closing Tag
		output << Content << "</" << Tag << ">";
	}
}