# Get All Files to Build
file(GLOB CoherentUIOpenGLGUI_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
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