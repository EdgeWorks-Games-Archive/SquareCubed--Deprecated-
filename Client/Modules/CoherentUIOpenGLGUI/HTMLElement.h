#pragma once

#include <ostream>
#include <string>

namespace CoherentUIOpenGLUI {
	class HTMLElement final {
	public: // Properties
		std::string Tag;
		std::string Content;
		std::string ID;
		std::string Style; // < TODO: Remove with style tuple list

	public:
		HTMLElement(std::string tag);
		void Generate(std::ostream &output);
	};
}