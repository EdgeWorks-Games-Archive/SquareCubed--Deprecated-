#include "HTMLElement.h"

namespace CoherentUIOpenGLUI {
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