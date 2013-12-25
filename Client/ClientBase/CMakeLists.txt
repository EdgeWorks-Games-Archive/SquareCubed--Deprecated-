# Get All Files to Build
file(GLOB ClientBase_SRC
	"*.h"
	"*.cpp"
	"*.h.in"
	"*.cpp.in"
)

# Group Files into Source Groups
source_group (Content FILES
	Content.h Content.cpp
	IContentBase.h
)
source_group (Context FILES
	IContext.h IWindow.h
)
source_group (Core FILES
	Engine.h Engine.cpp
)
source_group (Graphics FILES
	ICamera.h
	IGraphics.h
	IGraphicsFactory.h
)
source_group ("Graphics\\Content Types" FILES
	ITexture2D.h
	ITileArray.h
)
source_group (Graphics\\Renderers FILES
	IAgentRenderer.h
	ISelectionRenderer.h
	ITileRenderer.h
)
source_group (GUI FILES
	IGUI.h
	IGUIBindings.h
)
source_group (Input FILES
	Input.h Input.cpp
	InputData.h
)
source_group (Network FILES
	INetwork.h
	INetworkFactory.h
	IPacketHandler.h
)
source_group ("Network\\Handler Callbacks" FILES
	IAgentsCallback.h
	IMainMenuCallback.h
	IPlayerCallback.h
	IWorldCallback.h
)
source_group ("Network\\Packet Dispatchers" FILES
	IGameDispatcher.h
	IPlayerDispatcher.h
)
source_group (StateEngine FILES
	IState.h
	StateEngine.h StateEngine.cpp
)
source_group (StateEngine FILES
	IState.h
	StateEngine.h StateEngine.cpp
)
source_group (Tools\\Agents FILES
	Agents.h Agents.cpp
	BaseAgentTypes.h BaseAgentTypes.cpp
	PlayerAgent.h PlayerAgent.cpp
	AgentSelect.h AgentSelect.cpp
)
source_group (Tools\\Player FILES
	RPGPlayer.h RPGPlayer.cpp
)
source_group (Tools\\World FILES
	World.h World.cpp
	WorldProvider.h WorldProvider.cpp
)

# Add Library Build Output
add_library (ClientBase ${ClientBase_SRC})

# Link Required Libraries
target_link_libraries (ClientBase CommonLib)

# Set Directory
set_property (TARGET ClientBase PROPERTY FOLDER "Client")