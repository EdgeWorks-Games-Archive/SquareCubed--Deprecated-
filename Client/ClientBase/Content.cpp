#include "Content.h"

#include <CommonLib/LoggingManager.h>

#include <algorithm>

namespace Content {
	// Initialization/Uninitialization

	Content::Content(Utils::ILoggingManager &logManager) :
		m_Logger(logManager.CreateLogger("Content")),
		m_ContentList()
	{
		m_Logger.LogInfo("Content Initialized");
	}

	Content::~Content() {
		ClearContent();
	}

	// Internal Wrapped Utility Functions

	IContentBase& Content::GetContent(IContentFactory &type, std::string path) {
		// Transform the string so we can avoid duplicates better
		std::transform(path.begin(), path.end(), path.begin(), ::tolower);

		// Check if it already exists, if yes return it
		for (ContentEntry &entry : m_ContentList) {
			// Same Type?
			if (entry.Type == type.GetTypeName()) {
				// Same Path?
				if (entry.Path == path) {
					// And Return it
					return *entry.C;
				}
			}
		}

		// Since it doesn't exist, create it
		ContentEntry contentEntry(
			type.GetTypeName(),
			path,
			type.New(path)
			);

		// Add it to the list
		m_ContentList.push_back(contentEntry);

		// Log it
		m_Logger.LogInfo("Loaded new %s: %s", type.GetTypeName(), path.c_str());

		// And Return it
		return *contentEntry.C;
	}

	// Content Utility Functions

	void Content::ClearContent() {
		for (std::vector<int>::size_type i = 0; i != m_ContentList.size(); i++)
			delete m_ContentList[i].C;
		m_ContentList.clear();

		m_Logger.LogHighlight("Cleared all Content");
	}
}