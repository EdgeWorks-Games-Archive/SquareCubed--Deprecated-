# Get All Files in the current directory to Build
file (GLOB Physics_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Define Source Groups
source_group ("" FILES
	CollisionResolver.h CollisionResolver.cpp
	DataTypes.h DataTypes.cpp
	Physics.h Physics.cpp
)
source_group (Broadphase FILES
	AABBBroadphase.h AABBBroadphase.cpp
	IBroadphase.h
)
source_group (Colliders FILES
	CircleCollider.h CircleCollider.cpp
	Collider.h
)
source_group (RigidBodies FILES
	DynamicRigidBody.h DynamicRigidBody.cpp
	IRigidBody.h IRigidBody.cpp
)

# Add Library Build Output
add_library (Physics ${Physics_SRC})

# Set Directory
set_property (TARGET Physics PROPERTY FOLDER "Common")