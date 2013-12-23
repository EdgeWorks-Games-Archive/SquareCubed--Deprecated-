# Add Dependency Variables
set (DEPENDENCY_DIR "" CACHE PATH "Dependency folder path.")

# Make Sure Variables are Correctly Configured
if (NOT EXISTS ${DEPENDENCY_DIR})
	message (FATAL_ERROR "You need to configure the dependency path to a valid path.")
endif ()

# Configure GLM
include (CMakeDependencyGLM.txt)