#include "Units.h"

#include <ClientBase/IGraphics.h>
#include <ClientBase/IGraphicsFactory.h>
#include <ClientBase/IUnitRenderer.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IPacketHandler.h>

namespace Tools {
	namespace Units {
		// Initialization/Uninitialization

		Units::Units(Network::INetwork &networkFactory, Graphics::IGraphics &graphics, Physics::Physics &physics, std::string tileArrayPath) :
			m_Renderer(graphics.GetFactory().CreateUnitRenderer(
				graphics.GetFactory().GetTileArray(tileArrayPath)
			)),

			m_Network(networkFactory),
			m_Handler(m_Network.GetFactory().CreateUnitsHandler(*this)),

			m_Units(),

			m_Physics(physics)
		{
			m_Network.Attach(*m_Handler);
		}

		Units::~Units() {
			m_Network.Detach(*m_Handler);
		}

		// Units Management Utility Functions

		void Units::AddUnit(IUnit *unit) {
			m_Units.push_front(std::unique_ptr<IUnit>(unit));
		}

		void Units::RemoveUnit(UnitID unitId) {
			auto it = m_Units.begin();
			while (it != m_Units.end()) {
				if ((*it)->ID == unitId) {
					// Found it!
					it = m_Units.erase(it);
					return;
				}
				else
					++it;
			}
		}

		void Units::UpdateUnit(UnitID unitId, DataTypes::Health health, unsigned int graphicId) {
			for (std::unique_ptr<IUnit> &unit : m_Units) {
				if (unit->ID == unitId) {
					// Update Unit Data
					unit->GraphicID = std::move(graphicId);
					unit->Health = std::move(health);
					return;
				}
			}

			// Not found, throw Exception
			throw std::exception("Unit not Found");
		}

		bool Units::UnitExists(UnitID unitId) {
			for (std::unique_ptr<IUnit> &unit : m_Units) {
				if (unit->ID == unitId)
					return true;
			}

			// Not found, return false
			return false;
		}

		const std::list<std::unique_ptr<IUnit>>& Units::GetAllUnits() {
			return m_Units;
		}

		// Game Loop

		void Units::RenderUnits() {
			m_Renderer->RenderUnits(m_Units);
		}

		// Callback Functions

		void Units::ReceivedUpdateUnitPhysics(const unsigned int unitId, const CNetwork::PhysicsUpdateData &data) {
			for (std::unique_ptr<IUnit> &unit : m_Units) {
				if (unit->ID == unitId) {
					// Update the Unit's Position
					unit->ReceivedUpdatePhysics(data);
					return;
				}
			}
		}

		void Units::ReceivedUnitDesc(unsigned int unitId, DataTypes::Health health, unsigned int graphicId) {
			// Add new Unit if it doesn't exist
			// TODO: change this to GetPlayer returning a pointer instead that can be nullptr
			if (!UnitExists(unitId))
				AddUnit(new PhysicsUnit(unitId, health, m_Physics));

			// Update the (newly created?) Unit
			UpdateUnit(unitId, std::move(health), graphicId);
		}

		void Units::ReceivedRemoveUnit(unsigned int unitId) {
			// Remove the Unit
			RemoveUnit(unitId);
		}
	}
}