#pragma once

#include "Renderer.h"

#include "CoherentUI.h"
#include <Coherent/UI/Binding/EventHandler.h>
#include <Coherent/UI/View.h>

#include <CommonLib/Events.h>

namespace CoherentUIOpenGLUI {
	class ViewEventListener final : public Coherent::UI::ViewListener {
		Renderer &m_Renderer;
		Coherent::UI::View *m_View;

	public: // Initialization/Uninitialization
		ViewEventListener(Renderer &renderer);
		~ViewEventListener();

	public: // Events
		Utils::Event<Utils::EmptyEventArgs> OnViewReady;
		Utils::Event<Utils::EmptyEventArgs> OnViewReadyForBindings;

	public: // Utility Functions
		Coherent::UI::View& GetView() const { return *m_View; }

	public: // Coherent UI Functions
		virtual void OnViewCreated(Coherent::UI::View *view) COHERENT_OVERRIDE;
		virtual void OnDraw(Coherent::UI::CoherentHandle handle, bool useSharedMemory, int width, int height) COHERENT_OVERRIDE;
		virtual void CreateSurface(bool useSharedMemory, unsigned width, unsigned height, Coherent::UI::SurfaceResponse *response) COHERENT_OVERRIDE;
		virtual void DestroySurface(Coherent::UI::CoherentHandle surface, bool useSharedMemory) COHERENT_OVERRIDE;
		virtual void OnReadyForBindings(int frameId, const wchar_t* url, bool isMainFrame);
	};
}