/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation;
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include "uwb-module-ndle-protocol.h"
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("UwbModuleNdleProtocol");

	UwbModuleNdleProtocol::UwbModuleNdleProtocol()
	{
		NS_LOG_FUNCTION(this);
	}

	UwbModuleNdleProtocol::~UwbModuleNdleProtocol()
	{
		NS_LOG_FUNCTION(this);

	}

	Ptr<Packet> UwbModuleNdleProtocol::GeneratePingPacket(const Mac64Address & senderAddress, const Mac64Address & leaderMac)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[16];

		senderAddress.CopyTo(buffer);
		leaderMac.CopyTo(buffer + 8);

		Ptr<Packet> packet = Create<Packet>(buffer, 16);

		return packet;

	}

	Mac64Address UwbModuleNdleProtocol::GetSenderAddress(Ptr<const Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);

		static uint8_t buffer[16];

		Mac64Address address;

		packet->CopyData(buffer, 16);
		address.CopyFrom(buffer);

		return address;

	}

	Mac64Address UwbModuleNdleProtocol::GetLeaderAddress(Ptr<const Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);

		static uint8_t buffer[16];

		Mac64Address address;

		packet->CopyData(buffer, 16);
		address.CopyFrom(buffer + 8);

		return address;
	}
}