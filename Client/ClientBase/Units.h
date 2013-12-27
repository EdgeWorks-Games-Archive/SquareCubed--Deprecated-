#pragma once

#include "Types.h"

#include <ClientBase/IUnitsCallback.h>
#include <ClientBase/BaseUnitTypes.h>

#include <memory>
#include <list>

namespace Physics {
	class Physics;
}

namespace Tools {
	namespace Units {
		/** Client-side representation of server object by the same name. */
		class Units final : public Network::IUnitsCallback {
			// Renderer
			std::unique_ptr<Graphics::IUnitRenderer> m_Renderer;

			// Networking
			Network::INetwork &m_Network;
			std::unique_ptr<Network::IPacketHandler> m_Handler;

			// Units Container
			std::list<std::unique_ptr<IUnit>> m_Units;

			// External Modules
			Physics::Physics &m_Physics;

		public: // Initialization/Uninitialization
			Units(Core::Engine &engine, Physics::Physics &physics, std::string tileArrayPath);
			~Units();

		protected: // Internal Unit Management Helpers
			friend class Player::RPGPlayer; // < This class knows what it's doing
			void AddUnit(IUnit *unit);
			void RemoveUnit(UnitID unitId);
			void UpdateUnit(UnitID unitId, DataTypes::Health health, unsigned int graphicId);

		public: // Unit Management Utility Functions
			bool UnitExists(UnitID unitId);
			const std::list<std::unique_ptr<IUnit>>& GetAllUnits();

		public: // Game Loop
			void RenderUnits();
			
		public: // Callback Functions
			void ReceivedUpdateUnitPhysics(const unsigned int unitId, const CNetwork::PhysicsUpdateData &data);
			void ReceivedUnitDesc(unsigned int unitId, DataTypes::Health health, unsigned int graphicId);
			void ReceivedRemoveUnit(unsigned int unitId);
		};
	}
}