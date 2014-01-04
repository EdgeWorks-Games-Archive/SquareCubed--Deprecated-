#include "UnitsPacketHandler.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/IUnitsCallback.h>

#include <CRakNetNetwork/PacketTypes.h>
#include <CommonLib/PhysicsPacketDataTypes.h>

#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	UnitsPacketHandler::UnitsPacketHandler(Network::INetwork &network, Network::IUnitsCallback &callback) :
		m_Network(network),
		m_Callback(callback)
	{
	}

	// Game Loop

	bool UnitsPacketHandler::HandlePacket(RakNet::Packet &packet) {
		switch (packet.data[0]) {
		case (int) GamePacketIDType::UnitPhysicsUpdate: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int unitId;
			bs.Read(unitId);

			CNetwork::PhysicsUpdateData data;
			bs.Read(data.Position.x);
			bs.Read(data.Position.y);
			bs.Read(data.Rotation);
			bs.Read(data.Velocity.x);
			bs.Read(data.Velocity.y);
			bs.Read(data.TargetVelocity.x);
			bool s = bs.Read(data.TargetVelocity.y);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedUpdateUnitPhysics(unitId, data);
			} return true;
		case (int) GamePacketIDType::UnitDesc: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int unitId;
			bs.Read(unitId);

			DataTypes::Health health;
			bs.Read(health.Current);
			bs.Read(health.Max);

			unsigned int graphicId;
			bool s = bs.Read(graphicId);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedUnitDesc(std::move(unitId), std::move(health), std::move(graphicId));
			} return true;
		case (int) GamePacketIDType::UnitRemove: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int unitId;
			bool s = bs.Read(unitId);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedRemoveUnit(unitId);
			} return true;
		}

		return false;
	}
}