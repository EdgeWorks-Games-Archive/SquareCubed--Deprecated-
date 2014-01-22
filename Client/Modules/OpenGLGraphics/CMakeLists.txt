# Get All Files to Build
file(GLOB OpenGLGraphics_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group ("" FILES
	OpenGLCamera.h
	OpenGLGraphics.h OpenGLGraphics.cpp
	OpenGLGraphicsFactory.h OpenGLGraphicsFactory.cpp
	OpenGLGraphicsLoader.h
)
source_group ("Content Types" FILES
	Texture2D.h Texture2D.cpp
	TileArray.h TileArray.cpp
)
source_group ("Header Wrappers" FILES
	GLheaders.h
	ILheaders.h
)
source_group (Renderers FILES
	UnitRenderer.h UnitRenderer.cpp
	SelectionRenderer.h SelectionRenderer.cpp
	TileRenderer.h TileRenderer.cpp
)

# Add Library Build Output
add_library (OpenGLGraphics ${OpenGLGraphics_SRC})

# DevIL Doesn't Use Relative Paths
include_directories (${DEPENDENCY_DIR}/devil/include)

# Link Required Libraries
target_link_libraries (OpenGLGraphics ClientBase)
target_link_libraries (OpenGLGraphics opengl32)
target_link_libraries (OpenGLGraphics glu32)
target_link_libraries (OpenGLGraphics debug glfw3debug)
target_link_libraries (OpenGLGraphics optimized glfw3release)
target_link_libraries (OpenGLGraphics DevIL)
target_link_libraries (OpenGLGraphics ILU)
target_link_libraries (OpenGLGraphics glew32)

# Set Directory
set_property (TARGET OpenGLGraphics PROPERTY FOLDER "Client/Modules")