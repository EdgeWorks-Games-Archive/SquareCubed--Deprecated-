#pragma once

#include <ostream>
#include <string>
#include <forward_list>

namespace CoherentUIOpenGLUI {
	class HTMLHelper {
	public:
		/** HTML Escapes characters in a string.
		 * \param[in,out] data The string to escape.
		 */
		static void Escape(std::string &data);
	};

	class HTMLElement final {
		std::forward_list<std::string> m_StyleEntries;

	public: // Properties
		std::string Tag;
		std::string Content;
		std::string ID;

	public:
		HTMLElement(std::string tag);

		template <typename T>
		void AddStyle(std::string key, T entry) {
			std::stringstream entryStream;
			entryStream << key << ":" << entry << ";";
			m_StyleEntries.push_front(entryStream.str());
		}

		void Generate(std::ostream &output);
	};
}