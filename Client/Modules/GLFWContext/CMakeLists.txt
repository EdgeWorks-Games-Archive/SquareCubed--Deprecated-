# Get All Files to Build
file(GLOB GLFWContext_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Add Library Build Output
add_library (GLFWContext ${GLFWContext_SRC})

# Link Required Libraries
target_link_libraries (GLFWContext ClientBase)
target_link_libraries (GLFWContext debug glfw3debug)
target_link_libraries (GLFWContext optimized glfw3release)

# Set Directory
set_property (TARGET GLFWContext PROPERTY FOLDER "Client/Modules")