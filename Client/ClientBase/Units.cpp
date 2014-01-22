#include "Units.h"

#include "Engine.h"
#include "IGraphics.h"
#include "IGraphicsFactory.h"
#include "IUnitRenderer.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IPacketHandler.h"

namespace Tools {
	namespace Units {
		// Initialization/Uninitialization

		Units::Units(Core::Engine &engine, Physics::Physics &physics, std::string tileArrayPath) :
			m_Renderer(engine.GetGraphics().GetFactory().CreateUnitRenderer(
				engine.GetGraphics().GetFactory().GetTileArray(tileArrayPath)
			)),

			m_Network(engine.GetNetwork()),
			m_Handler(m_Network.GetFactory().CreateUnitsHandler(*this)),

			m_Units(),

			m_Physics(physics)
		{
			m_Network.Attach(*m_Handler);
		}

		Units::~Units() {
			m_Network.Detach(*m_Handler);
		}

		// Internal Unit Management Helpers

		void Units::Add(IUnit *unit) {
			m_Units.push_front(std::unique_ptr<IUnit>(unit));
		}

		void Units::Remove(UnitID unitId) {
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

		void Units::Update(UnitID unitId, DataTypes::Health health, unsigned int graphicId) {
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

		// Units Management Utility Functions

		bool Units::UnitExists(UnitID unitId) {
			for (std::unique_ptr<IUnit> &unit : m_Units) {
				if (unit->ID == unitId)
					return true;
			}

			// Not found, return false
			return false;
		}

		const std::list<std::unique_ptr<IUnit>>& Units::GetAll() {
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
				Add(new DynamicUnit(unitId, health, m_Physics));

			// Update the (newly created?) Unit
			Update(unitId, std::move(health), graphicId);
		}

		void Units::ReceivedRemoveUnit(unsigned int unitId) {
			// Remove the Unit
			Remove(unitId);
		}
	}
}