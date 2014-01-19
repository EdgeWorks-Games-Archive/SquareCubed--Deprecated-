#pragma once

#include <ostream>
#include <string>
#include <sstream>
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
		std::forward_list<std::string> m_AttributeEntries;
		std::forward_list<std::string> m_StyleEntries;
		std::forward_list<std::string> m_ClassEntries;

	public: // Properties
		std::string Tag;
		std::string Content;
		std::string ID;

	public:
		HTMLElement();

		template <typename T>
		void AddAttribute(std::string key, T entry) {
			std::stringstream entryStream;
			entryStream << " " << key << "=\"" << entry << "\"";
			m_AttributeEntries.push_front(entryStream.str());
		}

		template <typename T>
		void AddStyle(std::string key, T entry) {
			std::stringstream entryStream;
			entryStream << key << ":" << entry << ";";
			m_StyleEntries.push_front(entryStream.str());
		}

		void AddClass(std::string className) {
			m_ClassEntries.push_front(std::move(className));
		}
		
		void Generate(std::ostream &output);
	};
}