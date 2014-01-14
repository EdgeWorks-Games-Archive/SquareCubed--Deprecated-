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
		void Generate(std::ostream &output);

	private: // Internal Generation Helpers
		void GenerateBody(std::ostream &output);

	public: // Adding Subcomponents
		GUI::ILabelGenerator& AddLabel(std::string text);
		GUI::IDynamicLabelGenerator& AddDynamicLabel(std::unique_ptr<GUI::IDynamicLabel> &bindingObject, std::string text);

	private: // Subcomponent Helpers
		template<class T> T& AddNew();
		template<class T, class BindingT> T& AddNew(std::unique_ptr<BindingT> &bindingObject);
	};
}