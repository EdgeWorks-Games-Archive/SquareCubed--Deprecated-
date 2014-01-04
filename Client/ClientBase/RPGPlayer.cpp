#include "RPGPlayer.h"

#include "Engine.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IPlayerDispatcher.h"
#include "IPacketHandler.h"
#include "Input.h"
#include "IGraphics.h"
#include "ICamera.h"
#include "Units.h"
#include "PlayerUnit.h"

#include <CommonLib/ILoggingManager.h>

namespace Tools {
	namespace Player {
		// Initialization/Uninitialization
		RPGPlayer::RPGPlayer(Core::Engine &engine, Tools::Units::Units &units, Physics::Physics &physics) :
			m_Logger(engine.GetLoggingManager().CreateLogger("Player")),

			m_Network(engine.GetNetwork()),
			m_Input(engine.GetInput()),
			m_Units(units),
			m_Physics(physics),

			m_Unit(nullptr),
			m_PacketHandler(m_Network.GetFactory().CreatePlayerHandler(*this)),
			m_Dispatcher(m_Network.GetFactory().CreatePlayerDispatcher()),

			m_Speed(2.0f),
			m_Deadzone(0.4f),

			m_Camera(engine.GetGraphics().GetMainCamera()),
			m_CameraPosition(m_Camera.GetPosition()),
			m_CameraSize(m_Camera.GetSize())

		{
			m_Network.Attach(*m_PacketHandler);
		}

		// Because of the unique_ptr being defined with an incomplete type
		// the destructor has to be implemented in the .cpp file.
		RPGPlayer::~RPGPlayer() {
			m_Network.Detach(*m_PacketHandler);
		}

		// Network Callback Functions

		void RPGPlayer::ReceivedPlayerDesc(unsigned int unitId, DataTypes::Health health) {
			m_Unit = new Tools::Units::PlayerUnit(std::move(unitId), std::move(health), m_Physics);
			m_Units.Add(m_Unit);
			m_Logger.LogInfo("Player Spawned");
		}

		// Game Loop

		void RPGPlayer::Update(float delta) {
			if (m_Unit != nullptr) {
				Input::AxisDesc inpVal = m_Input.GetMovementAxis();
				if (inpVal.Any) {
					// Change Character Force
					m_Unit->RigidBody.TargetVelocity.x = inpVal.Scaled.x * m_Speed;
					m_Unit->RigidBody.TargetVelocity.y = inpVal.Scaled.y * m_Speed;

					// Rotate Character
					m_Unit->Rotation = inpVal.Angle;
				}
				else {
					// Reset Character Force
					m_Unit->RigidBody.TargetVelocity.x = 0;
					m_Unit->RigidBody.TargetVelocity.y = 0;
				}

				// Check if Force Changed
				if (m_PreviousForce != m_Unit->RigidBody.TargetVelocity) {
					// Send Updated Physics to Server
					m_Dispatcher->SendPlayerPhysics(m_Unit->RigidBody, m_Unit->Rotation.Radians);

					// Update Previous Force
					m_PreviousForce = m_Unit->RigidBody.TargetVelocity;
				}

				// Set Camera Position
				float xOffset = m_CameraSize.x / 2 * m_Deadzone;
				float yOffset = m_CameraSize.y / 2 * m_Deadzone;
				float leftMax = m_Unit->GetPosition().x - xOffset;
				float rightMax = m_Unit->GetPosition().x + xOffset;
				float downMax = m_Unit->GetPosition().y - yOffset;
				float upMax = m_Unit->GetPosition().y + yOffset;

				if (m_CameraPosition.x < leftMax)
					m_CameraPosition.x = leftMax;
				if (m_CameraPosition.x > rightMax)
					m_CameraPosition.x = rightMax;
				if (m_CameraPosition.y < downMax)
					m_CameraPosition.y = downMax;
				if (m_CameraPosition.y > upMax)
					m_CameraPosition.y = upMax;
			}
		}
	}
}