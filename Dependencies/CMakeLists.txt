# Add Dependency Variables
set (DEPENDENCY_DIR "" CACHE PATH "Dependency folder path.")

# Make Sure Variables are Correctly Configured
if (NOT EXISTS ${DEPENDENCY_DIR})
	message (SEND_ERROR "You need to configure the dependency path to a valid path.")
else ()
	# Configure CoherentUI
	include (CMakeDependencyCoherentUI.txt)

	# Configure DevIL
	include (CMakeDependencyDevIL.txt)

	# Configure GLEW
	include (CMakeDependencyGLEW.txt)

	# Configure GLFW
	include (CMakeDependencyGLFW.txt)

	# Configure GLM
	include (CMakeDependencyGLM.txt)

	# Configure RakNet
	include (CMakeDependencyRakNet.txt)
endif ()