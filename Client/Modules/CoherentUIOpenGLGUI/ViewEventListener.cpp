#include "ViewEventListener.h"

#include "SharedMemoryHelper.h"

#include "CoherentUI.h"
#include <Coherent/UI/View.h>

#include <assert.h>

namespace CoherentUIOpenGLUI {
	ViewEventListener::ViewEventListener(Renderer &renderer) :
		m_Renderer(renderer),
		m_View(nullptr)
	{}

	ViewEventListener::~ViewEventListener() {
		if (m_View)
			m_View->Destroy();
	}

	void ViewEventListener::OnViewCreated(Coherent::UI::View *view) {
		m_View = view;
		m_View->SetFocus();
		OnViewReady.Invoke(Utils::NO_ARGS);
	}

	void ViewEventListener::OnDraw(Coherent::UI::CoherentHandle handle, bool useSharedMemory, int width, int height) {
		assert(useSharedMemory);
		const size_t pixelSize = sizeof(unsigned);
		const unsigned int surfaceWidth = (unsigned int) width;
		const unsigned int surfaceHeight = (unsigned int) height;

		const size_t size = surfaceWidth * surfaceHeight * pixelSize;
		unsigned int* map = (unsigned int*) SharedMemoryHelper::Map(handle, size);

		// Copy the received data to OpenGL
		glBindTexture(GL_TEXTURE_2D, m_Renderer.GetTextureID());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surfaceWidth, surfaceHeight, GL_BGRA, GL_UNSIGNED_BYTE, map);
		glBindTexture(GL_TEXTURE_2D, 0);

		SharedMemoryHelper::Unmap(map, size);
	}

	void ViewEventListener::CreateSurface(bool useSharedMemory, unsigned width, unsigned height, Coherent::UI::SurfaceResponse *response) 	{
		assert(useSharedMemory);
		const size_t pixelSize = sizeof(unsigned);
		const size_t sizeInBytes = width * height * pixelSize;
		Coherent::UI::CoherentHandle sharedHandle = SharedMemoryHelper::CreateSegment(sizeInBytes);

		response->Signal(sharedHandle);
	}

	void ViewEventListener::DestroySurface(Coherent::UI::CoherentHandle surface, bool useSharedMemory) {
		assert(useSharedMemory);
		SharedMemoryHelper::DestroySegment(surface);
	}

	void ViewEventListener::OnReadyForBindings(int frameId, const wchar_t* url, bool isMainFrame) {
		OnViewReadyForBindings.Invoke(Utils::NO_ARGS);
	}
}