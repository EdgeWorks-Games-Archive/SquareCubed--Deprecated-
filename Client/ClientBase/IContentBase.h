#pragma once

namespace Content {
	class IContentBase {
		// Prevent Copies
		IContentBase(const IContentBase&);

	public:
		IContentBase() {}
		virtual ~IContentBase() {}
	};
}