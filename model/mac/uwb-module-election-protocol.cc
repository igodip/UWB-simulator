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

#include "uwb-module-election-protocol.h"
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleElectionProtocol");

	UwbModuleElectionProtocol::UwbModuleElectionProtocol()
	{
		NS_LOG_FUNCTION(this);


	}

	UwbModuleElectionProtocol::~UwbModuleElectionProtocol()
	{
		NS_LOG_FUNCTION(this);

	}

	Ptr<Packet> UwbModuleElectionProtocol::GeneratePingPacket(const Mac64Address & senderAddress)
	{

		NS_LOG_FUNCTION(this << senderAddress);

		static uint8_t buffer[8];

		NS_LOG_INFO(senderAddress);

		senderAddress.CopyTo(buffer);
		Ptr<Packet> packet = Create<Packet>(buffer, 8);

		return packet;

	}

	Mac64Address UwbModuleElectionProtocol::GetAddress(Ptr<const Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);

		static uint8_t buffer[8];
		packet->CopyData(buffer, 8);

		Mac64Address address;
		address.CopyFrom(buffer);

		return address;

	}
}