# Add Dependency Variables
set (DEPENDENCY_DIR "" CACHE PATH "Dependency folder path.")

# Make Sure Variables are Correctly Configured
if (NOT EXISTS ${DEPENDENCY_DIR})
	message (SEND_ERROR "You need to configure the dependency path to a valid path.")
else ()
	# Configure GLM
	include (CMakeDependencyGLM.txt)

	# Configure GLFW
	include (CMakeDependencyGLFW.txt)

	# Configure RakNet
	include (CMakeDependencyRakNet.txt)
endif ()