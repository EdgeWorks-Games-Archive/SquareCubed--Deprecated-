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
install (TARGETS Client DESTINATION Bin)

# Set Directory
SET_PROPERTY(TARGET Client PROPERTY FOLDER "Client")