# Get All Files to Build
file(GLOB CoherentUIOpenGLGUI_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group ("" FILES
	CoherentUIOpenGLUI.h CoherentUIOpenGLUI.cpp
	CoherentUIOpenGLUILoader.h
	LogHandler.h LogHandler.cpp
	Renderer.h Renderer.cpp
	SharedMemoryHelper.h SharedMemoryHelperWin.cpp
)
source_group (Bindings FILES
	GUIBindings.h GUIBindings.cpp
)
source_group ("Event Listeners" FILES
	SystemEventListener.h SystemEventListener.cpp
	ViewEventListener.h ViewEventListener.cpp
)
source_group ("Header Wrappers" FILES
	CoherentUI.h
	GLheaders.h
)
source_group (Elements FILES
	View.h View.cpp
	Label.h Label.cpp
)
source_group (Elements\\Helpers FILES
	HTMLElement.h HTMLElement.cpp
)

# Add Library Build Output
add_library (CoherentUIOpenGLGUI ${CoherentUIOpenGLGUI_SRC})

# DevIL Doesn't Use Relative Paths
include_directories (${DEPENDENCY_DIR}/devil/include)

# And I also wanna get CoherentUI just working quickly
include_directories (${DEPENDENCY_DIR}/CoherentUI/include)

# Link Required Libraries
target_link_libraries (CoherentUIOpenGLGUI ClientBase)
target_link_libraries (CoherentUIOpenGLGUI ${DEPENDENCY_COHERENT_LIB})

# Set Directory
set_property (TARGET CoherentUIOpenGLGUI PROPERTY FOLDER "Client/Modules")