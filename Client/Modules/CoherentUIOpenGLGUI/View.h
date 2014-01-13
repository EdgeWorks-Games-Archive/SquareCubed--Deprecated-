#pragma once

#include <ClientBase/IView.h>

#include <list>
#include <memory>
#include <string>

namespace CoherentUIOpenGLUI {
	class View final : public GUI::IView {
		std::wstring m_Path;

	public:
		View(std::wstring path);
		const std::wstring& GetPath();
	};

	class ViewGenerator final : public GUI::IViewGenerator {
		std::list<std::unique_ptr<GUI::IElementGenerator>> m_ElementGenerators;

	public: // Generation
		std::unique_ptr<GUI::IView> GenerateView();
		void Generate(std::ofstream &file);

	public: // Adding Subcomponents
		GUI::ILabelGenerator& AddLabel(std::string text);
	};
}