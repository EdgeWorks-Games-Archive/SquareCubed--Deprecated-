# Get All Files to Build
file(GLOB Client_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Executable Build Output
add_executable (Client ${Client_SRC})

# Link Required Libraries
target_link_libraries (Client ClientBase)
target_link_libraries (Client ClientRakNetNetwork)
target_link_libraries (Client CoherentUIOpenGLGUI)
target_link_libraries (Client GLFWContext)
target_link_libraries (Client OpenGLGraphics)
target_link_libraries (Client MainMenuState)
target_link_libraries (Client GameState)

# Add Installer Details
install (TARGETS Client DESTINATION ./ COMPONENT Client)

# Additional DLLs
install (FILES
	"${DEPENDENCY_DIR}/CoherentUI/lib/${DEPENDENCY_COHERENT_LIB_SUBFOLDER}/${DEPENDENCY_COHERENT_LIB}.dll"
	"${DEPENDENCY_DIR}/devil/bin/DevIL.dll"
	"${DEPENDENCY_DIR}/devil/bin/ILU.dll"
	"${DEPENDENCY_DIR}/glew/bin/glew32.dll"
	DESTINATION ./
	COMPONENT Client
)

# Set Directory
set_property (TARGET Client PROPERTY FOLDER "Client")