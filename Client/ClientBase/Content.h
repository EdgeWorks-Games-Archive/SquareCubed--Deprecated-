#pragma once

#include "IContentBase.h"

#include <CommonLib/Logger.h>

#include <string>
#include <type_traits>
#include <vector>

namespace Content {
	class IContentFactory {
	public:
		~IContentFactory() {}

		virtual IContentBase* New(const std::string &path) = 0;
		virtual const char* GetTypeName() = 0;
	};

	template <class T> class ContentFactory : public IContentFactory {
	public:
		IContentBase* New(const std::string &path) { return new T(path); }
		const char* GetTypeName() { return T::GetType(); }
	};

	template <class T, class Param> class ParamContentFactory : public IContentFactory {
		Param m_Param;
	public:
		ParamContentFactory(Param param) : m_Param(param) {}
		IContentBase* New(const std::string &path) { return new T(path, m_Param); }
		const char* GetTypeName() { return T::GetType(); }
	};

	/// <summary>
	/// Implementations IContent INetwork are responsible for managing content.
	/// Content is any type of data loaded in from files. The implementation needs
	/// to prevent duplicate loading of content.
	/// </summary>
	class Content final {
		// Internal Content Entry
		struct ContentEntry {
			const std::string Type;
			const std::string Path;
			IContentBase* C;

			ContentEntry(const char* type, std::string path, IContentBase* c) :
				Type(type),
				Path(path),
				C(c)
			{}
		};

		// Logger
		Utils::Logger m_Logger;

		// Storage of Content Entries
		std::vector<ContentEntry> m_ContentList;

	public: // Initialization/Uninitialization
		Content(Utils::ILoggingManager &logManager);
		~Content();

	private: // Internal Wrapped Utility Functions
		IContentBase& GetContent(IContentFactory &type, std::string path);

	public: // Content Utility Functions
		/// <summary>
		/// Retrieves content of type T associated with path.
		/// Creates new class of type T if no content of this type has been previously associated with path.
		/// </summary>
		/// <param name="path">The path.</param>
		/// <returns>Requested Content</returns>
		template <class T> T& GetContent(const std::string &path) {
			// Make sure the template derives from IContentBase
			static_assert(
				std::is_base_of<IContentBase, T>::value,
				"GetContent requires a type derived from Content::IContentBase"
			);

			// Actually call the wrapped function
			return (T&) GetContent(ContentFactory<T>(), path);
		}

		/// <summary>
		/// Retrieves content of type T associated with path.
		/// Creates new class of type T with parameter param if no content
		/// of this type has been previously associated with path.
		/// </summary>
		/// <param name="path">The path.</param>
		/// <param name="param">The parameter.</param>
		/// <returns>Requested Content</returns>
		template <class T, class Param> T& GetContent(const std::string &path, Param param) {
			// Make sure the template derives from IContentBase
			static_assert(
				std::is_base_of<IContentBase, T>::value,
				"GetContent requires a type derived from Content::IContentBase"
			);

			// Actually call the wrapped function
			return (T&) GetContent(ParamContentFactory<T, Param>(param), path);
		}

		void ClearContent();
	};
}