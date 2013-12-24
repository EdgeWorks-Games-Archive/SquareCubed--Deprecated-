#pragma once

namespace GUI { class IGUI; }
namespace Input { class Input; }
namespace Utils { class ILoggingManager; }

namespace CoherentUIOpenGLUI {
	// Use this function to create a new CoherentUIOpenGLLoader object without
	// including CoherentUIOpenGL.h (and the includes that come with it)
	GUI::IGUI* LoadGUI(Utils::ILoggingManager &logManager, Input::Input &input);
}